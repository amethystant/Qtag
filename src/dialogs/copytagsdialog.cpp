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


#include "dialogs/copytagsdialog.h"
#include "core/main.h"
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>

CopyTagsDialog::CopyTagsDialog(QWidget *parent, FileList *listOfFiles) : QDialog(parent) {

    setWindowTitle("Copy Tags");
    this->listOfFiles = listOfFiles;

    sourceFile = NULL;
    targetFile = NULL;

    targetTagLabel = new QLabel("Target tag:", this);
    targetFileLabel = new QLabel("Target file:", this);
    sourceFileLabel = new QLabel("Source file:", this);
    sourceTagLabel = new QLabel("Source Tag:", this);

    sourceFileSelection = new QComboBox(this);
    sourceTagSelection = new QComboBox(this);
    targetFileSelection = new QComboBox(this);
    targetTagSelection = new QComboBox(this);

    okButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Cancel", this);

    sourceTagSelection->setEnabled(false);
    targetTagSelection->setEnabled(false);
    okButton->setEnabled(false);

    QObject::connect(sourceFileSelection, SIGNAL(currentIndexChanged(int)), this, SLOT(updateComboBoxes()));
    QObject::connect(targetFileSelection, SIGNAL(currentIndexChanged(int)), this, SLOT(updateComboBoxes()));
    QObject::connect(okButton, SIGNAL(clicked()), this, SLOT(startCopying()));
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    initComboBoxes();
    createLayout();

}

void CopyTagsDialog::initComboBoxes() {

    int i;
    for(i = 0; i < listOfFiles->length(); i++) {
        QString path = listOfFiles->at(i)->getPath();
        sourceFileSelection->addItem(path);
        targetFileSelection->addItem(path);
    }

}

void CopyTagsDialog::createLayout() {

    QGridLayout* layout = new QGridLayout(this);
    int i = 0;
    layout->addWidget(sourceFileLabel, i, 0);
    layout->addWidget(sourceFileSelection, i, 1);
    i++;
    layout->addWidget(sourceTagLabel, i, 0);
    layout->addWidget(sourceTagSelection, i, 1);
    i++;
    layout->addWidget(targetFileLabel, i, 0);
    layout->addWidget(targetFileSelection, i, 1);
    i++;
    layout->addWidget(targetTagLabel, i, 0);
    layout->addWidget(targetTagSelection, i, 1);
    i++;
    layout->addWidget(cancelButton, i, 0);
    layout->addWidget(okButton, i, 3);

}

/*
 * This method is called when the user clicks on a QComboBox and changes
 * the source file or the target file. Determines which tags
 * exist in the selected files and the updates the other QComboBoxes.
*/
void CopyTagsDialog::updateComboBoxes() {

    QString selectedFile = sourceFileSelection->currentText();
    AudioFile* file;
    int i;
    for(i = 0; i < listOfFiles->length(); i++) {
        AudioFile* f = listOfFiles->at(i);
        if(f->getPath().compare(selectedFile) == 0) {
            file = f;
            i = listOfFiles->length();
        }
    }

    if(file != sourceFile) {

        sourceTagSelection->clear();

        if(file->hasApeTag())
            sourceTagSelection->addItem(QString::fromStdString(NamesOfTags::APE));
        if(file->hasAsfTag())
            sourceTagSelection->addItem(QString::fromStdString(NamesOfTags::ASF));
        if(file->hasId3v1())
            sourceTagSelection->addItem(QString::fromStdString(NamesOfTags::ID3V1));
        if(file->hasId3v2())
            sourceTagSelection->addItem(QString::fromStdString(NamesOfTags::ID3V2));
        if(file->hasInfoTag())
            sourceTagSelection->addItem(QString::fromStdString(NamesOfTags::INFO));
        if(file->hasXiphComment())
            sourceTagSelection->addItem(QString::fromStdString(NamesOfTags::XIPH));

        sourceTagSelection->setEnabled(true);
        sourceFile = file;

    }

    selectedFile = targetFileSelection->currentText();
    for(i = 0; i < listOfFiles->length(); i++) {
        AudioFile* f = listOfFiles->at(i);
        if(f->getPath().compare(selectedFile) == 0) {
            file = f;
            i = listOfFiles->length();
        }
    }

    if(file != targetFile) {

        targetTagSelection->clear();

        if(file->hasApeTag())
            targetTagSelection->addItem(QString::fromStdString(NamesOfTags::APE));
        if(file->hasAsfTag())
            targetTagSelection->addItem(QString::fromStdString(NamesOfTags::ASF));
        if(file->hasId3v1())
            targetTagSelection->addItem(QString::fromStdString(NamesOfTags::ID3V1));
        if(file->hasId3v2())
            targetTagSelection->addItem(QString::fromStdString(NamesOfTags::ID3V2));
        if(file->hasInfoTag())
            targetTagSelection->addItem(QString::fromStdString(NamesOfTags::INFO));
        if(file->hasXiphComment())
            targetTagSelection->addItem(QString::fromStdString(NamesOfTags::XIPH));

        targetTagSelection->setEnabled(true);
        targetFile = file;

    }

    if(targetTagSelection->isEnabled() && sourceTagSelection->isEnabled())
        okButton->setEnabled(true);
    else
        okButton->setDisabled(true);

}

void CopyTagsDialog::copyTags(AudioTag *sourceTag, AudioTag *targetTag) {

    targetTag->setTitle(sourceTag->getTitle());
    targetTag->setTrack(sourceTag->getTrack());
    targetTag->setGenre(sourceTag->getGenre());
    targetTag->setComment(sourceTag->getComment());
    targetTag->setAlbum(sourceTag->getAlbum());
    targetTag->setArtist(sourceTag->getArtist());
    targetTag->setYear(sourceTag->getYear());

}

void CopyTagsDialog::startCopying() {

    QMessageBox* message = new QMessageBox(this);
    message->setStandardButtons(QMessageBox::NoButton);
    message->setText("Please wait...");
    message->setWindowTitle("Copying...");
    message->show();

    copyTags(sourceFile->getTagByName(sourceTagSelection->currentText()),
             targetFile->getTagByName(targetTagSelection->currentText()));

    targetFile->save();

    message->close();
    delete message;
    close();

}
