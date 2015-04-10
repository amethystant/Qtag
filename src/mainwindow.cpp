#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "copytagsdialog.h"
#include "multipletaggingdialog.h"
#include "main.h"
#include "createalbumdialog.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    openedFile = NULL;
    ui->setupUi(this);
    ui->lineEdit_path->setReadOnly(true);
    unsavedChanges = false;
    setIcons();

    QObject::connect(ui->actionOpenFile, SIGNAL(triggered()), this, SLOT(openFile()));
    QObject::connect(ui->actionOpenDirectory, SIGNAL(triggered()), this, SLOT(openDirectory()));
    QObject::connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
                     this, SLOT(openInEditor(QTreeWidgetItem*)));
    QObject::connect(ui->actionSaveAll, SIGNAL(triggered()), this, SLOT(saveAll()));
    QObject::connect(ui->actionClose_all, SIGNAL(triggered()), this, SLOT(closeAll()));
    QObject::connect(ui->actionCopy_tags, SIGNAL(triggered()), this, SLOT(openCopyTagsDialog()));
    QObject::connect(ui->actionMultipleTagging, SIGNAL(triggered()), this, SLOT(openMultipleTaggingDialog()));
    QObject::connect(ui->actionCreate_album_from_folder, SIGNAL(triggered()),
                     this, SLOT(openCreateAlbumDialog()));
    QObject::connect(ui->pushButton_closeFile, SIGNAL(clicked()), this, SLOT(closeCurrentFile()));
    QObject::connect(ui->pushButton_saveFile, SIGNAL(clicked()), this, SLOT(saveCurrentFile()));
    QObject::connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(ui->lineEdit_path, SIGNAL(textChanged(QString)), this, SLOT(updateWindowTitle()));

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setIcons() {

    ui->actionQuit->setIcon(QIcon::fromTheme("application-exit", QIcon(":/application-exit.png")));
    ui->actionCopy_tags->setIcon(QIcon::fromTheme("edit-copy", QIcon(":/copytags.png")));
    ui->actionCreate_album_from_folder->setIcon(QIcon::fromTheme("media-optical", QIcon(":/createalbum.png")));
    ui->actionAbout->setIcon(QIcon::fromTheme("help-about", QIcon(":/info.png")));
    ui->actionOpenDirectory->setIcon(QIcon::fromTheme("folder-open", QIcon(":/opendirectory.png")));
    ui->actionOpenFile->setIcon(QIcon::fromTheme("document-open", QIcon(":/openfile.png")));
    ui->actionHow_to_contribute->setIcon(QIcon::fromTheme("help-about", QIcon(":/info.png")));
    ui->actionLicense->setIcon(QIcon::fromTheme("help-about", QIcon(":/info.png")));
    ui->actionMultipleTagging->setIcon(QIcon::fromTheme("format-justify-fill",
                                                        QIcon(":/multipletagging.png")));
    ui->actionSaveAll->setIcon(QIcon::fromTheme("document-save", QIcon(":/save.png")));
    ui->actionSettings->setIcon(QIcon::fromTheme("preferences-system", QIcon(":/settings.png")));

}

/*
Opens the file dialog and then calls a method to update the tree widget
*/
void MainWindow::openFile() {

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setOption(QFileDialog::DontUseNativeDialog);
#ifdef WIN32
    dialog.setDirectory("C:/");
#else
    dialog.setDirectory("/home");
#endif
    dialog.setNameFilter(
                tr(NAME_FILTER.c_str()));
    dialog.setViewMode(QFileDialog::Detail);
    dialog.show();
    if(dialog.exec()) {

        QStringList selectedFiles = dialog.selectedFiles();
        int numOfFiles = selectedFiles.length();
        int i;
        for(i = 0; i < numOfFiles; i++) {

            QString path = selectedFiles.value(i);
            if(!isFileOnList(path)) {
                AudioFile *newFile = new AudioFile(path, this);
                listOfFiles.append(newFile);
            }

        }

    }

    updateViews();

}

/*
This two structs are used only in the method above.
They do not have any special meaning, but they are necessary to sort
 the files and add them to the tree widget.
*/
typedef struct {
    QList<AudioFile*> listOfFiles;
    QString name;
} Album;

typedef struct {
    QList<Album> listOfAlbums;
    QString name;
} Artist;

/*
Updates the tree widget.
*/
void MainWindow::updateViews() {

    ui->treeWidget->clear();
    QList<Artist> listOfArtists;
    int i;
    for(i = 0; i < listOfFiles.length(); i++) {

        AudioFile *f = listOfFiles.at(i);
        int i1 = 0;
        bool isArtistOnList = false;
        while(i1 < listOfArtists.length() && !isArtistOnList) {
            if(listOfArtists.at(i1).name.compare(f->getArtist()) == 0) {
                isArtistOnList = true;
            } else {
                i1++;
            }
        }
        if(!isArtistOnList) {

            Artist newArtist;
            newArtist.name = f->getArtist();
            QList<Album> newAlbumList;
            Album newAlbum;
            newAlbum.name = f->getAlbum();
            newAlbum.listOfFiles.append(f);
            newAlbumList.append(newAlbum);
            newArtist.listOfAlbums.append(newAlbumList);
            listOfArtists.append(newArtist);

        } else {

            int index = i1;
            Artist artist = listOfArtists.at(index);
            i1 = 0;
            bool isAlbumOnList = false;
            while(i1 < artist.listOfAlbums.length() && !isAlbumOnList) {
                if(artist.listOfAlbums.at(i1).name.compare(f->getAlbum()) == 0) {
                    isAlbumOnList = true;
                } else {
                    i1++;
                }
            }

            if(!isAlbumOnList) {
                Album newAlbum;
                newAlbum.name = f->getAlbum();
                newAlbum.listOfFiles.append(f);
                artist.listOfAlbums.append(newAlbum);
            } else {
                int index1 = i1;
                Album al = artist.listOfAlbums.at(index1);
                al.listOfFiles.append(f);
                artist.listOfAlbums.replace(index1, al);
            }

            listOfArtists.replace(index, artist);
        }

    }

    for(i = 0; i < listOfArtists.length(); i++) {

        QTreeWidgetItem *artistItem = new QTreeWidgetItem();
        Artist artist = listOfArtists.at(i);
        if(artist.name.isEmpty())
            artistItem->setText(0, "<unknown artist>");
        else
            artistItem->setText(0, artist.name);

        int i1;
        for(i1 = 0; i1 < artist.listOfAlbums.length(); i1++) {
            Album album = artist.listOfAlbums.at(i1);
            QTreeWidgetItem *albumItem = new QTreeWidgetItem();
            if(album.name.isEmpty())
                albumItem->setText(0, "<unknown album>");
            else
                albumItem->setText(0, album.name);

            int i2;
            for(i2 = 0; i2 < album.listOfFiles.length(); i2++) {

                AudioFile *f = album.listOfFiles.at(i2);
                QTreeWidgetItem *fileItem = new QTreeWidgetItem();
                if(f->getName().isEmpty())
                    fileItem->setText(0, "<unknown track>");
                else
                    fileItem->setText(0, f->getName());
                fileItem->setText(1, f->getPath());

                albumItem->addChild(fileItem);
            }

            artistItem->addChild(albumItem);
        }

        ui->treeWidget->addTopLevelItem(artistItem);
    }

    ui->treeWidget->expandAll();

}

/*
Opens the "folder dialog", which allows user to select a whole directory to open.
*/
void MainWindow::openDirectory() {

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    dialog.setOption(QFileDialog::DontUseNativeDialog);
#ifdef WIN32
    dialog.setDirectory("C:/");
#else
    dialog.setDirectory("/home");
#endif
    dialog.setViewMode(QFileDialog::Detail);
    dialog.show();
    if(dialog.exec()) {

        QDir dir(dialog.selectedFiles().at(0));
        QStringList listOfContent = dir.entryList(QDir::Files);
        int i;
        for(i = 0; i < listOfContent.length(); i++) {
            QString s = dir.absoluteFilePath(listOfContent.at(i));
            if((s.endsWith(".mp3", Qt::CaseInsensitive) ||
                          s.endsWith(".flac", Qt::CaseInsensitive) ||
                          s.endsWith(".wav", Qt::CaseInsensitive) ||
                          s.endsWith(".wv", Qt::CaseInsensitive) ||
                          s.endsWith(".ogg", Qt::CaseInsensitive) ||
                          s.endsWith(".wma", Qt::CaseInsensitive) ||
                          s.endsWith(".asf", Qt::CaseInsensitive) ||
                          s.endsWith(".wave", Qt::CaseInsensitive) ) && !isFileOnList(s)) {
                AudioFile *newFile = new AudioFile(s, this);
                listOfFiles.append(newFile);
            }
        }

    }

    updateViews();

}

bool MainWindow::isFileOnList(QString path) {
    int i = 0;
    while(i < listOfFiles.length()) {
        if(path.compare(listOfFiles.at(i)->getPath()) == 0)
            return true;
        i++;
    }

    return false;
}

void MainWindow::openInEditor(QTreeWidgetItem *file) {

    int i = 0;
    if(file->childCount()>0)
        return;
    while(i < listOfFiles.length()) {

        if(file->text(1).compare(listOfFiles.at(i)->getPath()) == 0) {
            openedFile = listOfFiles.at(i);
            i = listOfFiles.length();
        } else {
            i++;
        }

    }

    updateEditor();

}

/*
Updates the dock widget. Sets the selected file's "editorLayout" member
as the layout of the widget.
*/
void MainWindow::updateEditor() {

    if(openedFile == NULL) {
        ui->lineEdit_path->clear();
        ui->label_type_value->clear();
        ui->label_bitrate_value->clear();
        ui->label_channels_value->clear();
        ui->label_length_value->clear();
        ui->label_sampleRate_value->clear();
        QWidget* w = new QWidget(this);
        ui->dockWidget_tags->setWidget(w);
        return;
    }
    ui->lineEdit_path->setText(openedFile->getPath());

    QString type = openedFile->getType();
    QString bitrate = intToString(openedFile->getBitrate());
    bitrate.append(" kb/s");
    QString channels = intToString(openedFile->getChannels());
    QString length = intToString(openedFile->getLength()/60);
    length.append(":");
    QString seconds = intToString(openedFile->getLength()%60);
    if(seconds.length() == 1) {
        seconds.insert(0, '0');
    }
    length.append(seconds);
    length.append(" min");
    QString sampleRate = intToString(openedFile->getSampleRate());
    sampleRate.append(" Hz");
    ui->label_type_value->setText(type);
    ui->label_bitrate_value->setText(bitrate);
    ui->label_channels_value->setText(channels);
    ui->label_length_value->setText(length);
    ui->label_sampleRate_value->setText(sampleRate);

    TagEditorLayout* editorLayout = findLayout(openedFile);
    QWidget* w = new QWidget(ui->dockWidget_tags);
    w->setLayout(editorLayout);
    QScrollArea* scrollArea = new QScrollArea(ui->dockWidget_tags);
    scrollArea->setWidget(w);
    scrollArea->setWidgetResizable(true);
    ui->dockWidget_tags->setWidget(scrollArea);
    ui->dockWidget_tags->show();

}

/*
 * Returns the TagEditorLayout for a specific AudioFile object.
 * If there is not the right TagEditorLayout on the list, it returns NULL or it creates
 *  a new TagEditorLayout and adds it to the list (depending on the value of the second parameter)
*/
TagEditorLayout* MainWindow::findLayout(AudioFile *file, bool create) {

    int i;
    for(i = 0; i < listOfLayouts.length(); i++) {
        TagEditorLayout* l = listOfLayouts.at(i);
        if(l->getFile()->getPath() == file->getPath()) {
            return l;
        }
    }

    if(!create) {
        return NULL;
    } else {
        TagEditorLayout* l = new TagEditorLayout(this, file);
        QObject::connect(l, SIGNAL(fileEdited()), this, SLOT(fileEdited()));
        listOfLayouts.append(l);
        return l;
    }

}

Ui::MainWindow* MainWindow::getUI() {
    return ui;
}

/*
 * This slot saves all files which has been opened in the editor
*/
void MainWindow::saveAll() {

    if(listOfLayouts.length() == 0) {
        return;
    }
    QMessageBox* message = new QMessageBox(this);
    message->setWindowTitle("Saving...");
    message->setText("Please wait...");
    message->setStandardButtons(QMessageBox::NoButton);
    message->show();

    int i;
    for( i = 0; i < listOfLayouts.length(); i++ ) {
        TagEditorLayout* l = listOfLayouts.at(i);
        l->getFile()->save();
    }

    unsavedChanges = false;
    updateViews();

    message->setText("Done.");
    message->setStandardButtons(QMessageBox::Ok);
    message->update();

}

void MainWindow::openCopyTagsDialog() {
    if(unsavedChanges) {
        if(QMessageBox::question(this, "Copying tags",
                                 "Do you want to save all files before copying tags?") == QMessageBox::Yes)
            saveAll();

    }
    closeEditor();
    listOfLayouts.clear();
    CopyTagsDialog* dialog = new CopyTagsDialog(this, &listOfFiles);
    dialog->exec();
    reloadAllFiles();
    updateViews();

}

void MainWindow::closeCurrentFile() {
    closeFile(listOfFiles.indexOf(openedFile));
}

void MainWindow::closeAll() {

    if(unsavedChanges) {
        if(QMessageBox::question(this, "Save all?", "There are some unsaved changes\n"
                                                 "Save all?") == QMessageBox::Yes) {
            saveAll();
        }

    }

    if(listOfFiles.isEmpty()) {
        return;
    }

    while(listOfFiles.length() > 0) {
        closeFile(0);
    }
}

void MainWindow::saveCurrentFile() {

    if(openedFile == NULL) {
        return;
    }
    QDialog* dialog = new QDialog(this);
    QLabel* label = new QLabel("Saving...", dialog);
    QGridLayout* layout = new QGridLayout(dialog);
    layout->addWidget(label);
    dialog->setLayout(layout);
    dialog->setBaseSize(300, 200);
    dialog->setWindowTitle("Saving...");
    dialog->show();

    openedFile->save();
    updateViews();

    label->setText("Saved.");
    QPushButton* button = new QPushButton("OK", dialog);
    QObject::connect(button, SIGNAL(clicked()),dialog, SLOT(close()));
    layout->addWidget(button, 1, 1);
    dialog->update();
}

void MainWindow::openMultipleTaggingDialog() {

    if(unsavedChanges) {
        if(QMessageBox::question(this, "Copying tags",
                                 "Do you want to save all files before copying tags?") == QMessageBox::Yes)
            saveAll();
    }
    closeEditor();
    listOfLayouts.clear();
    MultipleTaggingDialog* dialog = new MultipleTaggingDialog(this);
    dialog->exec();
    reloadAllFiles();
    updateViews();

}

void MainWindow::fileEdited() {
    unsavedChanges = true;
}


void MainWindow::openCreateAlbumDialog() {

    if(unsavedChanges) {
        if(QMessageBox::question(this, "Create album",
                                 "Do you want to save all files before copying tags?") == QMessageBox::Yes)
            saveAll();
    }
    closeEditor();
    listOfLayouts.clear();
    CreateAlbumDialog* dialog = new CreateAlbumDialog(this);
    dialog->exec();
    reloadAllFiles();
    updateViews();

}

void MainWindow::updateWindowTitle() {

    if(ui->lineEdit_path->text().isEmpty()) {
        setWindowTitle("Qtag");
    } else {
        int i = ui->lineEdit_path->text().lastIndexOf('/');
        QString fileName = ui->lineEdit_path->text();
        fileName.remove(0, i+1);
        setWindowTitle(fileName + " - Qtag");
    }

}

void MainWindow::reloadAllFiles() {

    listOfLayouts.clear();
    closeEditor();
    updateViews();
    for(int i = 0; i < listOfFiles.length(); i++) {
        AudioFile* f = new AudioFile(listOfFiles.at(i)->getPath(), this);
        listOfFiles.removeAt(i);
        listOfFiles.insert(i, f);
    }

}

void MainWindow::closeFile(int i) {

    AudioFile* f = listOfFiles.at(i);
    TagEditorLayout* l = findLayout(f, false);
    if(l != NULL) {
        listOfLayouts.removeOne(l);
    }
    if(openedFile == f) {
        openedFile = NULL;
    }
    listOfFiles.removeOne(f);
    updateViews();
    updateEditor();

}

void MainWindow::closeFile(QString path) {

    for(int i = 0; i < listOfFiles.length(); i++) {
        if(listOfFiles.at(i)->getPath() == path) {
            closeFile(i);
        }
    }

}

void MainWindow::closeEditor() {
    openedFile = NULL;
    updateEditor();
}
