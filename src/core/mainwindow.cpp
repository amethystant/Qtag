/*
 *    Qtag is an advanced but simple to use audio metadata editor. Runs on Linux
 *    and Windows. Supports many formats, including MPEG, Ogg Vorbis, Wave and FLAC
 *
 *    Copyright (C) 2015 - 2016  Karel Patlejch <kaja.patlejch@gmail.com>
 *
 *    Used libraries:
 *      TagLib - http://taglib.github.io/
 *      Qt - http://qt.io
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License along
 *    with this program; if not, write to the Free Software Foundation, Inc.,
 *    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#include "core/mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogs/multipletaggingdialog.h"
#include "core/main.h"
#include "dialogs/createalbumdialog.h"
#include "dialogs/configdialog.h"
#include "core/qtagapp.h"
#include <QFileInfo>
#include <QMessageBox>
#include <QGridLayout>

MainWindow::MainWindow(QtagApp *app) : QMainWindow(), ui(new Ui::MainWindow) {

    listOfFiles = app->getFileList();
    this->app = app;
    ui->setupUi(this);
    ui->lineEdit_path->setReadOnly(true);
    setIcons();

    updateViews();

    spacer = new QSpacerItem(1, 100000, QSizePolicy::Maximum, QSizePolicy::Maximum);
    ui->gridLayout_3->addItem(spacer, ui->gridLayout_3->rowCount()+1, 1);

    QObject::connect(app, SIGNAL(fileListChanged()), this, SLOT(fileListChangeUpdate()));
    QObject::connect(ui->actionOpenFile, SIGNAL(triggered()), this, SLOT(openFileDialog()));
    QObject::connect(ui->actionOpenDirectory, SIGNAL(triggered()), this, SLOT(openDirectory()));
    QObject::connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
                     this, SLOT(openInEditor(QTreeWidgetItem*)));
    QObject::connect(ui->actionSaveAll, SIGNAL(triggered()), this, SLOT(saveAll()));
    QObject::connect(ui->actionClose_all, SIGNAL(triggered()), this, SLOT(closeAll()));
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
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {

    if(unsavedChanges() && askBeforeClosing() == QMessageBox::Cancel)
        return;
    QMainWindow::closeEvent(event);

}

void MainWindow::setIcons() {

    QSettings settings;
    QString iconTheme = settings.value("icons", "native").toString();

    if(iconTheme == "native") {

        ui->actionQuit->setIcon(QIcon::fromTheme("application-exit", QIcon(":/images/application-exit.png")));
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

/*
Opens the file dialog and then calls a method to update the tree widget
*/
void MainWindow::openFileDialog() {

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
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
            app->openFile(path, false);

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
    for(i = 0; i < listOfFiles->length(); i++) {

        AudioFile *f = listOfFiles->at(i);
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
                app->openFile(s, false);
            }
        }

    }

    updateViews();

}

void MainWindow::openInEditor(QTreeWidgetItem *file) {

    int i = 0;
    if(file->childCount()>0)
        return;
    while(i < listOfFiles->length()) {

        if(file->text(1).compare(listOfFiles->at(i)->getPath()) == 0) {
            openedFile = listOfFiles->at(i)->getPath();
            i = listOfFiles->length();
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

    if(openedFile.isEmpty()) {
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
    ui->lineEdit_path->setText(openedFile);

    AudioFile* file = listOfFiles->getFileByPath(openedFile);

    QString type = file->getType();
    QString bitrate = intToString(file->getBitrate());
    bitrate.append(" kb/s");
    QString channels = intToString(file->getChannels());
    QString length = intToString(file->getLength()/60);
    length.append(":");
    QString seconds = intToString(file->getLength()%60);
    if(seconds.length() == 1) {
        seconds.insert(0, '0');
    }
    length.append(seconds);
    length.append(" min");
    QString sampleRate = intToString(file->getSampleRate());
    sampleRate.append(" Hz");
    ui->label_type_value->setText(type);
    ui->label_bitrate_value->setText(bitrate);
    ui->label_channels_value->setText(channels);
    ui->label_length_value->setText(length);
    ui->label_sampleRate_value->setText(sampleRate);

    QObject::connect(file, SIGNAL(editedOrSaved()), this, SLOT(updateWindowTitle()));

    TagEditorLayout* editorLayout = findLayout(file);
    QWidget* w = new QWidget(ui->dockWidget_tags);
    w->setLayout(editorLayout);
    QScrollArea* scrollArea = new QScrollArea(ui->dockWidget_tags);
    scrollArea->setWidget(w);
    scrollArea->setWidgetResizable(true);
    ui->dockWidget_tags->setWidget(scrollArea);
    ui->dockWidget_tags->show();

}

/*
 * This slot is called whenever a file is opened or closed.
 * Checks wheter the opened file is still on the list,
 * checks wheter all tag editor layouts still have their files on the list,
 * calls updateViews() and updateEditor()
 */
void MainWindow::fileListChangeUpdate() {

    if(!openedFile.isEmpty() && !listOfFiles->isFileOpened(openedFile)) {
        openedFile.clear();
    }

    int i = 0;
    while(i < listOfLayouts.length()) {
        if(!listOfFiles->isFileOpened(listOfLayouts.at(i)->getFile()->getPath())) {
            listOfLayouts.removeAt(i);
        } else {
            i++;
        }
    }

    updateEditor();
    updateViews();

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

    if(listOfFiles->length() == 0) {
        return;
    }
    QMessageBox* message = new QMessageBox(this);
    message->setWindowTitle("Saving...");
    message->setText("Please wait...");
    message->setStandardButtons(QMessageBox::NoButton);
    message->show();

    int i;
    for( i = 0; i < listOfFiles->length(); i++ ) {
        AudioFile* file = listOfFiles->at(i);
        file->save();
    }

    updateViews();

    message->close();
    delete message;
    updateWindowTitle();

}

void MainWindow::closeCurrentFile() {
    if(!openedFile.isEmpty())
        app->closeFile(listOfFiles->indexOf(listOfFiles->getFileByPath(openedFile)));
}

void MainWindow::closeAll() {

    if(unsavedChanges() && askBeforeClosing() == QMessageBox::Cancel) {
        return;
    }

    if(listOfFiles->isEmpty()) {
        return;
    }

    while(listOfFiles->length() > 0) {
        app->closeFile(0, false);
    }
    fileListChangeUpdate();
}

int MainWindow::askBeforeClosing() {

    QSettings settings;
    if(!settings.value("warnbeforeclosing", true).toBool())
        return QMessageBox::Discard;
    QMessageBox *msg = new QMessageBox(this);
    msg->setText("You are going to loose all unsaved changes. \n"
                 "Would you like to save all files?");
    msg->setWindowTitle("Save changes?");
    msg->setStandardButtons(QMessageBox::SaveAll | QMessageBox::Discard | QMessageBox::Cancel);
    QCheckBox* dontAskCheck = new QCheckBox("Don't ask me next time");
    msg->setCheckBox(dontAskCheck);
    msg->setDefaultButton(QMessageBox::SaveAll);
    msg->setEscapeButton(QMessageBox::Cancel);
    int response = msg->exec();
    if(response == QMessageBox::SaveAll) {
        saveAll();
    }

    if(dontAskCheck->isChecked()) {
        settings.setValue("warnbeforeclosing", false);
        settings.sync();
    }

    return response;

}

void MainWindow::saveCurrentFile() {

    if(openedFile.isEmpty()) {
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

    listOfFiles->getFileByPath(openedFile)->save();
    updateViews();

    dialog->close();
    delete dialog;
    updateWindowTitle();

}

void MainWindow::openMultipleTaggingDialog() {

    closeEditor();
    listOfLayouts.clear();
    MultipleTaggingDialog* dialog = new MultipleTaggingDialog(this, listOfFiles);
    dialog->exec();
    updateViews();

}

void MainWindow::openCreateAlbumDialog() {

    closeEditor();
    listOfLayouts.clear();
    CreateAlbumDialog* dialog = new CreateAlbumDialog(this, listOfFiles);
    dialog->exec();
    updateViews();

}

void MainWindow::updateWindowTitle() {

    if(openedFile.isEmpty()) {
        setWindowTitle("Qtag");
    } else {
        int i = ui->lineEdit_path->text().lastIndexOf('/');
        QString fileName = openedFile;
        fileName.remove(0, i + 1);
        AudioFile* file = listOfFiles->getFileByPath(openedFile);
        if(file->isEdited()) {
            fileName.append('*');
        }
        setWindowTitle(fileName + " - Qtag");
    }

}

void MainWindow::closeEditor() {
    openedFile.clear();
    updateEditor();
}

void MainWindow::openSettingsDialog() {
    ConfigDialog dialog(this);
    dialog.exec();
    setIcons();
}

bool MainWindow::unsavedChanges() {

    for(int i = 0; i < listOfFiles->length(); i++) {
        AudioFile *f = listOfFiles->at(i);
        if(f->isEdited()) {
            return true;
        }
    }

    return false;

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
                                              "Qtag is an audio tag editor based on Qt and TagLib<br>"
                                              "It's developed for Linux and Microsoft Windows<br>"
                                              "Supported formats: MP3, Ogg Vorbis, FLAC, ASF, WavPack, and WAV<br><br>"
                                              "© 2015 - 2016 by Karel Patlejch<br>"
                                              "Licensed under GNU General Public License 2.0<br>",
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

    QFile file(":/text_files/LICENSE_GPL");
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
