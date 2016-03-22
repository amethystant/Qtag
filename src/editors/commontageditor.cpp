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


#include "editors/commontageditor.h"

CommonTagEditor::CommonTagEditor(AudioTag *tag, QString nameOfTag, QWidget *parent) :
    QGroupBox(nameOfTag, parent) {

    this->tag = tag;
    layout = new QGridLayout(this);

    pictureLabel = new QLabel("Cover:", this);
    picturePath = new QString();
    picturePreview = new QLabel(this);
    picturePreview->setPixmap(QPixmap::fromImage(QImage(":images/nofile.png")));
    pictureSelection = new PictureSelectionButton(this, picturePath, picturePreview);
    extractPictureButton = new QPushButton("Save as a file...", this);
    removeCoverButton = new QPushButton("Remove cover", this);
    pictureFullSizeButton = new QPushButton("Show full size");
    coverArtActions = new CoverArtActions(this, picturePreview);
    coverArtActions->showPicturePreview(getPictureFromTag());

    if(!tag->supportsCoverArt()) {
        pictureLabel->setVisible(false);
        picturePreview->setVisible(false);
        pictureSelection->setVisible(false);
        extractPictureButton->setVisible(false);
        removeCoverButton->setVisible(false);
        pictureFullSizeButton->setVisible(false);
    }

    listOfEditors = new QList<LabelAndEditor*>();
    initEditors();

    QObject::connect(pictureSelection, SIGNAL(pictureChanged()), this, SLOT(updateTags()));
    QObject::connect(extractPictureButton, SIGNAL(clicked(bool)), this, SLOT(savePictureAsFile()));
    QObject::connect(pictureFullSizeButton, SIGNAL(clicked()), this, SLOT(showPictureFullSize()));
    QObject::connect(removeCoverButton, SIGNAL(clicked()), this, SLOT(removeCover()));

    createLayout();
}

void CommonTagEditor::initEditors() {

    QList<TagKey> listOfKeys = tag->getListOfSupportedKeys();
    int i;
    for (i = 0; i < listOfKeys.length(); i++) {

        TagKey key = listOfKeys.at(i);

        LabelAndEditor* labelAndEdit = new LabelAndEditor();
        labelAndEdit->key = key;
        labelAndEdit->editor = new QLineEdit(tag->getValue(key), this);
        labelAndEdit->label = new QLabel(QString(key.c_str()), this);
        QObject::connect(labelAndEdit->editor, SIGNAL(textEdited(QString)), this, SLOT(updateTags()));
        listOfEditors->append(labelAndEdit);

    }

}

/*
 *Overrides TagEditor::saveTags() and updates the genre tag
*/
void CommonTagEditor::updateTags() {

    if(!picturePath->isEmpty()) {
        tag->setCoverArt(*picturePath);
    }

    for(int i = 0; i < listOfEditors->length(); i++) {
        tag->setValue(listOfEditors->at(i)->key, listOfEditors->at(i)->editor->text());
    }
}

/*
 *Overrides TagEditor::createLayout() and adds the genre editor
 *to the layout
*/
void CommonTagEditor::createLayout() {

    int i = layout->rowCount();
    layout->addWidget(pictureLabel, i, 0);
    layout->addWidget(picturePreview, i, 1);
    i++;

    QHBoxLayout* l = new QHBoxLayout();
    l->addWidget(pictureSelection);
    l->addWidget(removeCoverButton);
    layout->addLayout(l, i, 0, 2, 0);
    i+=2;
    layout->addWidget(extractPictureButton, i, 0);
    layout->addWidget(pictureFullSizeButton, i, 1);

    i = layout->rowCount();
    for(int j = 0; j < listOfEditors->length(); j++) {
        layout->addWidget(listOfEditors->at(j)->label, i, 0);
        layout->addWidget(listOfEditors->at(j)->editor, i, 1);
        i++;
    }

    setLayout(layout);

}

void CommonTagEditor::savePictureAsFile() {
    coverArtActions->savePictureAsFile(getPictureFromTag());
}

void CommonTagEditor::showPictureFullSize() {
    coverArtActions->showPictureFullSize(getPictureFromTag());
}

QImage* CommonTagEditor::getPictureFromTag() {

    return tag->getCoverArt();

}

void CommonTagEditor::removeCover() {

    picturePath->clear();
    picturePreview->setPixmap(QPixmap::fromImage(QImage(":images/nofile.png")));
    tag->setCoverArt("");

}

