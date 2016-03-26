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


#include "ui/dialogs/createalbumdialog.h"
#include "core/main.h"
#include "actions/actions.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QGridLayout>
#include <QDir>
#include <QDirIterator>
#include <QRegExp>

CreateAlbumDialog::CreateAlbumDialog(QWidget *parent, FileList* list) :
    QDialog(parent) {

    fileList = list;

    directoryLabel = new QLabel("Root directory:", this);
    directoryEdit = new QLineEdit(this);
    directoryEdit->setReadOnly(true);
    directorySelectionButton = new QPushButton("Browse...", this);
    directoryGroup = new QGroupBox("Directory", this);

    tagFormatLabel = new QLabel("Tag format:", this);
    tagFormatEdit = new QLineEdit(this);
    hintButton = new QPushButton("Show hint", this);
    tagFormatGroup = new QGroupBox("Tag format", this);

    makeCapitalLettersCheck = new QCheckBox("capitalize letters", this);
    replaceStringLabel = new QLabel("Replace:", this);
    replaceStringEdit = new QLineEdit(this);
    replaceByLabel = new QLabel("Replace by:", this);
    replaceByEdit = new QLineEdit(this);
    additionalChangesGroup = new QGroupBox("Additional changes", this);

    apeCheck = new QCheckBox("APE tags", this);
    apeCheck->setChecked(true);
    asfCheck = new QCheckBox("ASF tags", this);
    asfCheck->setChecked(true);
    id3v1Check = new QCheckBox("ID3v1 tags", this);
    id3v1Check->setChecked(true);
    id3v2Check = new QCheckBox("ID3v2 tags", this);
    id3v2Check->setChecked(true);
    infoTagCheck = new QCheckBox("RIFF Info tags", this);
    infoTagCheck->setChecked(true);
    xiphCommentCheck = new QCheckBox("Xiph Comments", this);
    xiphCommentCheck->setChecked(true);
    tagsGroup = new QGroupBox("Apply to", this);

    startTaggingButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Cancel", this);

    setWindowTitle("Create album from path");
    createLayout();

    QObject::connect(directorySelectionButton, SIGNAL(clicked()), this, SLOT(openDirectorySelection()));
    QObject::connect(hintButton,SIGNAL(clicked()), this, SLOT(showHint()));
    QObject::connect(startTaggingButton, SIGNAL(clicked()), this, SLOT(startTagging()));
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));

}

void CreateAlbumDialog::createLayout() {

    QVBoxLayout* layout = new QVBoxLayout();
    setLayout(layout);

    QGridLayout* layout1 = new QGridLayout();
    layout1->addWidget(directoryLabel, 0, 0);
    layout1->addWidget(directoryEdit, 0, 1);
    layout1->addWidget(directorySelectionButton, 1, 0);
    directoryGroup->setLayout(layout1);

    QGridLayout* layout2 = new QGridLayout();
    layout2->addWidget(tagFormatLabel, 0, 0);
    layout2->addWidget(tagFormatEdit, 0, 1);
    layout2->addWidget(hintButton, 1, 0);
    tagFormatGroup->setLayout(layout2);

    QHBoxLayout* layout3 = new QHBoxLayout();
    layout3->addWidget(replaceStringLabel);
    layout3->addWidget(replaceStringEdit);
    QHBoxLayout* layout4 = new QHBoxLayout();
    layout4->addWidget(replaceByLabel);
    layout4->addWidget(replaceByEdit);
    QVBoxLayout* layout5 = new QVBoxLayout();
    layout5->addWidget(makeCapitalLettersCheck);
    layout5->addLayout(layout3);
    layout5->addLayout(layout4);
    additionalChangesGroup->setLayout(layout5);

    QGridLayout* layout6 = new QGridLayout();
    layout6->addWidget(apeCheck, 0, 0);
    layout6->addWidget(asfCheck, 0, 1);
    layout6->addWidget(id3v1Check, 1, 0);
    layout6->addWidget(id3v2Check, 1, 1);
    layout6->addWidget(infoTagCheck, 2, 0);
    layout6->addWidget(xiphCommentCheck, 2, 1);
    tagsGroup->setLayout(layout6);

    QHBoxLayout* layout7 = new QHBoxLayout();
    layout7->addWidget(startTaggingButton);
    layout7->addWidget(cancelButton);

    layout->addWidget(directoryGroup);
    layout->addWidget(tagFormatGroup);
    layout->addWidget(additionalChangesGroup);
    layout->addWidget(tagsGroup);
    layout->addLayout(layout7);

}

void CreateAlbumDialog::openDirectorySelection() {

    QFileDialog d(this);
    d.setFileMode(QFileDialog::DirectoryOnly);
    d.setViewMode(QFileDialog::Detail);
    d.show();
    if(d.exec()) {
        directoryEdit->setText(d.selectedFiles().at(0));
    }

}

/*
*Called when the user clicks on the button "show hint". 
*Displays a dialog with a review of the tag formating symbols
*/
void CreateAlbumDialog::showHint() {

    QDialog *hint = new QDialog(this);
    hint->setWindowTitle("Tag format - hint");
    QLabel* l  = new QLabel(hint);
    l->setText(
                "<b>Tag formating - symbols:</b> <br>"
                "/ - directory separator (like usually) <br>"
                "%a - artist <br>"
                "%l - album <br>"
                "%r - track number (can be both 01 or just 1)<br>"
                "%t - title<br>"
                "* - any string<br>"
                "? - any character<br>"
                "static strings (such as ---, _, -, etc) don't need to be in quotation marks<br><br>"
                "<b>Example:</b><br>"
                "<font color=green>%a/%l/%r---%t</font>         correct<br><br>"
                "<font color=red>%a/%l/%r---%t.ogg</font>       incorrect*<br>"
                "<font color=red>%a%l%t</font>                  incorrect**<br>"
                "<font color=red>%a?%l/*%r%t</font>             incorrect**<br><br>"
                "*The filename extension must NOT be included in the format<br>"
                "**All symbols and wildcards must be separated by a static string");
    QPushButton* b = new QPushButton("Close", hint);
    QObject::connect(b, SIGNAL(clicked()), hint, SLOT(close()));
    QVBoxLayout* lay = new QVBoxLayout(hint);
    lay->addWidget(l);
    lay->addWidget(b);
    hint->setLayout(lay);
    hint->show();

}

/*
* Called if a wrong tag format is recognized.
* Displays an error message.
*/
void CreateAlbumDialog::tagFormatError() {

    QMessageBox* message = new QMessageBox(this);
    message->setWindowTitle("Error");
    message->setText("Error - invalid tag format.");
    message->setStandardButtons(QMessageBox::Ok);
    message->exec();

}

void CreateAlbumDialog::saveTagsTo(AudioFile* f, TagFormat nameOfTag,
                                   QString title, QString track, QString album, QString artist) {

    AudioTag* t = f->getTagByName(nameOfTag);
    if(t == NULL) {
        return;
    }

    if(!title.isEmpty()) {
        t->setTitle(title);
    }
    if(!track.isEmpty()) {
        if(track.startsWith('0'))
            track.remove(0, 1);
        t->setTrack(track.toInt());
    }
    if(!album.isEmpty()) {
        t->setAlbum(album);
    }
    if(!artist.isEmpty()) {
        t->setArtist(artist);
    }

    f->save();

}

void CreateAlbumDialog::startTagging() {

    QMessageBox* message = new QMessageBox(this);
    message->setWindowTitle("Please wait");
    message->setText("Please wait, this may take a few seconds...");
    message->setStandardButtons(QMessageBox::NoButton);
    message->show();

    if(directoryEdit->text().isEmpty()) {
        QMessageBox* msg = new QMessageBox(this);
        msg->setText("Invalid path to the root directory.");
        msg->setStandardButtons(QMessageBox::Ok);
        msg->exec();
        message->done(1);
        return;
    }

    QList<TagFormat> formats;
    if(apeCheck->isChecked())
        formats.append(TagFormats::APE);
    if(asfCheck->isChecked())
        formats.append(TagFormats::ASF);
    if(id3v1Check->isChecked())
        formats.append(TagFormats::ID3V1);
    if(id3v2Check->isChecked())
        formats.append(TagFormats::ID3V2);
    if(xiphCommentCheck->isChecked())
        formats.append(TagFormats::XIPH);
    if(infoTagCheck->isChecked())
        formats.append(TagFormats::INFO);

    QList<AudioFile*>* taggedFiles;
    QString tagFormat = tagFormatEdit->text();
    taggedFiles = Actions::createAlbumFromDirectory(fileList, directoryEdit->text(),
                                                    formats, tagFormat);

    if(taggedFiles == NULL) {
        tagFormatError();
        message->done(1);
        return;
    } else if(taggedFiles->length() == 0) {
        QMessageBox* msg = new QMessageBox(this);
        msg->setWindowTitle("Error");
        msg->setText("No file matches the tag format.");
        msg->setStandardButtons(QMessageBox::Ok);
        msg->exec();
        message->done(1);
        return;
    }

    Actions::MultipleTaggingOptions options;

    options.album = false;
    options.artist = false;
    options.title = false;
    options.comment = false;
    options.genre = false;

    if(tagFormat.count("%t")) {
        options.title = true;
    }
    if(tagFormat.count("%a")) {
        options.artist = true;
    }
    if(tagFormat.count("%l")) {
        options.album = true;
    }

    if(!replaceStringEdit->text().isEmpty()) {
        for(int i = 0; i < taggedFiles->length(); i++) {
            Actions::replaceStringsInTags(taggedFiles->at(i), formats, options,
                                          replaceStringEdit->text(), replaceByEdit->text());
        }
    }

    if(makeCapitalLettersCheck->isChecked()) {
        for(int i = 0; i < taggedFiles->length(); i++) {
            Actions::capitalizeTags(taggedFiles->at(i), formats, options);
        }
    }

    message->close();
    delete message;
    close();

}
