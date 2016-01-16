/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 *
 * (C) 2015 by Karel Patlejch
 *
 * Used libraries:
 *    TagLib - https://github.com/taglib
 *    Qt - http://qt.io
 *
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "copytagsdialog.h"
#include "multipletaggingdialog.h"
#include "main.h"
#include "createalbumdialog.h"
#include "configdialog.h"
#include <QFileInfo>
#include <QMessageBox>
#include <QGridLayout>

MainWindow::MainWindow(QStringList files) :
    QMainWindow(),
    ui(new Ui::MainWindow),
    listOfFiles(this) {

    openedFile = NULL;
    ui->setupUi(this);
    ui->lineEdit_path->setReadOnly(true);
    setIcons();

    QSettings settings;

    if(!files.isEmpty()) {
        openFilesFromArguments(files);
    } else if(settings.value("openfiles", QVariant(false)).toBool()) {
        openLastSession();
    }
    updateViews();

    spacer = new QSpacerItem(1, 100000, QSizePolicy::Maximum, QSizePolicy::Maximum);
    ui->gridLayout_3->addItem(spacer, ui->gridLayout_3->rowCount()+1, 1);

    QObject::connect(ui->actionOpenFile, SIGNAL(triggered()), this, SLOT(openFileDialog()));
    QObject::connect(ui->actionOpenDirectory, SIGNAL(triggered()), this, SLOT(openDirectory()));
    QObject::connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
                     this, SLOT(openInEditor(QTreeWidgetItem*)));
    QObject::connect(ui->actionSaveAll, SIGNAL(triggered()), this, SLOT(saveAll()));
    QObject::connect(ui->actionClose_all, SIGNAL(triggered()), this, SLOT(closeAll()));
    QObject::connect(ui->actionCopy_tags, SIGNAL(triggered()), this, SLOT(openCopyTagsDialog()));
    QObject::connect(ui->actionMultipleTagging, SIGNAL(triggered()), this,
                     SLOT(openMultipleTaggingDialog()));
    QObject::connect(ui->actionCreateAlbumFromDirectory, SIGNAL(triggered()),
                     this, SLOT(openCreateAlbumDialog()));
    QObject::connect(ui->pushButton_closeFile, SIGNAL(clicked()), ui->actionClose_file, SLOT(trigger()));
    QObject::connect(ui->actionClose_file, SIGNAL(triggered()), this, SLOT(closeCurrentFile()));
    QObject::connect(ui->pushButton_saveFile, SIGNAL(clicked()), this, SLOT(saveCurrentFile()));
    QObject::connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(ui->lineEdit_path, SIGNAL(textChanged(QString)), this, SLOT(updateWindowTitle()));
    QObject::connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(openSettingsDialog()));
    QObject::connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(openAboutDialog()));
    QObject::connect(ui->actionLicense, SIGNAL(triggered()), this, SLOT(openLicenseDialog()));

}

MainWindow::~MainWindow() {
    saveSession();
    delete ui;
}

void MainWindow::setIcons() {

    QSettings settings;
    QString iconTheme = settings.value("icons", "native").toString();

    if(iconTheme == "native") {

        ui->actionQuit->setIcon(QIcon::fromTheme("application-exit", QIcon(":/images/application-exit.png")));
        ui->actionCopy_tags->setIcon(QIcon::fromTheme("edit-copy", QIcon(":/images/copytags.png")));
        ui->actionCreateAlbumFromDirectory->setIcon(QIcon::fromTheme("media-optical", QIcon(":/images/createalbum.png")));
        ui->actionAbout->setIcon(QIcon::fromTheme("help-about", QIcon(":/images/info.png")));
        ui->actionOpenDirectory->setIcon(QIcon::fromTheme("folder-open", QIcon(":/images/opendirectory.png")));
        ui->actionOpenFile->setIcon(QIcon::fromTheme("document-open", QIcon(":/images/openfile.png")));
        ui->actionLicense->setIcon(QIcon::fromTheme("help-about", QIcon(":/images/info.png")));
        ui->actionMultipleTagging->setIcon(QIcon::fromTheme("format-justify-fill",
                                                            QIcon(":/images/multipletagging.png")));
        ui->actionSaveAll->setIcon(QIcon::fromTheme("document-save", QIcon(":/images/save.png")));
        ui->actionSettings->setIcon(QIcon::fromTheme("preferences-system", QIcon(":/images/settings.png")));

    } else {

        ui->actionQuit->setIcon(QIcon(":/images/application-exit.png"));
        ui->actionCopy_tags->setIcon(QIcon(":/images/copytags.png"));
        ui->actionCreateAlbumFromDirectory->setIcon(QIcon(":/images/createalbum.png"));
        ui->actionAbout->setIcon(QIcon(":/images/info.png"));
        ui->actionOpenDirectory->setIcon(QIcon(":/images/opendirectory.png"));
        ui->actionOpenFile->setIcon(QIcon(":/images/openfile.png"));
        ui->actionLicense->setIcon(QIcon(":/images/info.png"));
        ui->actionMultipleTagging->setIcon(QIcon(":/images/multipletagging.png"));
        ui->actionSaveAll->setIcon(QIcon(":/images/save.png"));
        ui->actionSettings->setIcon(QIcon(":/images/settings.png"));

    }

}

void MainWindow::openFilesFromArguments(QStringList files) {
    for(int i = 0; i < files.length(); i++) {
        QFileInfo f(files.at(i));
        if(f.exists()) {
            openFile(files.at(i), false);
        }
    }
}

/*
Opens the file dialog and then calls a method to update the tree widget
*/
void MainWindow::openFileDialog() {

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
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
            openFile(path, false);

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
            if(s.endsWith(".mp3", Qt::CaseInsensitive) ||
                          s.endsWith(".flac", Qt::CaseInsensitive) ||
                          s.endsWith(".wav", Qt::CaseInsensitive) ||
                          s.endsWith(".wv", Qt::CaseInsensitive) ||
                          s.endsWith(".ogg", Qt::CaseInsensitive) ||
                          s.endsWith(".wma", Qt::CaseInsensitive) ||
                          s.endsWith(".asf", Qt::CaseInsensitive) ||
                          s.endsWith(".wave", Qt::CaseInsensitive)) {
                openFile(s, false);
            }
        }

    }

    updateViews();

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
        QObject::connect(l, SIGNAL(fileEdited()), this, SLOT(updateWindowTitle()));
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

    updateViews();

    message->setText("Done.");
    message->setStandardButtons(QMessageBox::Ok);
    message->update();
    updateWindowTitle();

}

void MainWindow::openCopyTagsDialog() {
    if(unsavedChanges()) {
        if(QMessageBox::question(this, "Copying tags",
                                 "Do you want to save all files before copying tags?") == QMessageBox::Yes)
            saveAll();

    }
    closeEditor();
    listOfLayouts.clear();
    CopyTagsDialog* dialog = new CopyTagsDialog(this, &listOfFiles);
    dialog->exec();
    updateViews();

}

void MainWindow::closeCurrentFile() {
    closeFile(listOfFiles.indexOf(openedFile));
}

void MainWindow::closeAll() {

    if(unsavedChanges()) {
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
    updateWindowTitle();

}

void MainWindow::openMultipleTaggingDialog() {

    if(unsavedChanges()) {
        if(QMessageBox::question(this, "Copying tags",
                                 "Do you want to save all files before multiple tagging?") == QMessageBox::Yes)
            saveAll();
    }
    closeEditor();
    listOfLayouts.clear();
    MultipleTaggingDialog* dialog = new MultipleTaggingDialog(this, &listOfFiles);
    dialog->exec();
    updateViews();

}

void MainWindow::openCreateAlbumDialog() {

    if(unsavedChanges()) {
        if(QMessageBox::question(this, "Create album",
                                 "Do you want to save all files before creating an album?") == QMessageBox::Yes)
            saveAll();
    }
    closeEditor();
    listOfLayouts.clear();
    CreateAlbumDialog* dialog = new CreateAlbumDialog(this, &listOfFiles);
    dialog->exec();
    updateViews();

}

void MainWindow::updateWindowTitle() {

    if(ui->lineEdit_path->text().isEmpty()) {
        setWindowTitle("Qtag");
    } else {
        int i = ui->lineEdit_path->text().lastIndexOf('/');
        QString fileName = ui->lineEdit_path->text();
        fileName.remove(0, i+1);
        TagEditorLayout* layout = findLayout(openedFile, false);
        if(layout != NULL && layout->isEdited()) {
            fileName.append('*');
        }
        setWindowTitle(fileName + " - Qtag");
    }

}

void MainWindow::openFile(QString path, bool update) {
    listOfFiles.addFileToList(path);
    if(update) {
        updateViews();
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
    listOfFiles.closeFile(i);
    updateEditor();
    updateViews();
}

void MainWindow::closeFile(QString path) {
    listOfFiles.closeFile(path);
    updateEditor();
    updateViews();
}

void MainWindow::closeEditor() {
    openedFile = NULL;
    updateEditor();
}

void MainWindow::openSettingsDialog() {
    ConfigDialog dialog(this);
    dialog.exec();
    setIcons();
}

bool MainWindow::unsavedChanges() {

    for(int i = 0; i < listOfLayouts.length(); i++) {
        TagEditorLayout* l = listOfLayouts.at(i);
        if(l->isEdited()) {
            return true;
        }
    }

    return false;

}

void MainWindow::saveSession() {

    QList<QVariant> list;
    for(int i = 0; i < listOfFiles.length(); i++) {
        QVariant member(listOfFiles.at(i)->getPath());
        list.append(member);
    }

    QSettings settings;
    settings.setValue("lastfiles", list);
    settings.sync();

}

void MainWindow::openLastSession() {
    QSettings settings;
    QList<QVariant> list = settings.value("lastfiles").toList();
    for(int i = 0; i < list.length(); i++) {
        openFile(list.at(i).toString(), false);
    }
    updateViews();
}

void MainWindow::openAboutDialog() {

    QDialog dialog;
    dialog.setWindowTitle("About Qtag");
    QVBoxLayout layout(&dialog);
    QHBoxLayout horizontalLayout(&dialog);
    QHBoxLayout buttonsLayout(&dialog);
    QLabel iconLabel(&dialog);
    iconLabel.setPixmap(QPixmap::fromImage(QImage(":/images/Qtag.png").scaled(150, 150)));
    QLabel descriptionLabel("<b>Qtag v" + QString::fromStdString(VERSION) +"</b><br>"
                                              "Qtag is an audio tag editor based on Qt and TagLib.<br>"
                                              "It is developed for Linux and it is also compatible with MS Windows<br>"
                                              "Supported formats: MP3, Ogg Vorbis, FLAC, ASF, WavPack, and WAV<br><br>"
                                              "© 2015 by Karel Patlejch<br>Licensed under Mozzila Public License 2.0<br>",
                            &dialog);
    QPushButton closeButton("Close", &dialog);
    QObject::connect(&closeButton, SIGNAL(clicked()), &dialog, SLOT(close()));

    horizontalLayout.addWidget(&iconLabel);
    horizontalLayout.addWidget(&descriptionLabel);
    buttonsLayout.addStretch(1);
    buttonsLayout.addWidget(&closeButton);
    layout.addLayout(&horizontalLayout);
    layout.addLayout(&buttonsLayout);
    dialog.exec();

}

void MainWindow::openLicenseDialog() {

    QFile file(":/text_files/LICENSE_MPL");
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream ts(&file);

    QDialog dialog;
    dialog.setWindowTitle("Qtag - license");
    QGridLayout layout(&dialog);
    QTextEdit license(&dialog);
    license.setText(ts.readAll());
    license.setReadOnly(true);
    QPushButton closeButton("Close", &dialog);
    QObject::connect(&closeButton, SIGNAL(clicked()), &dialog, SLOT(close()));
    layout.addWidget(&license, 0, 0);
    layout.addWidget(&closeButton, 1, 1);
    dialog.setLayout(&layout);
    dialog.resize(550, 390);
    dialog.exec();

}
