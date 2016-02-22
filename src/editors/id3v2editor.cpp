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


#include "editors/id3v2editor.h"

Id3v2Editor::Id3v2Editor(TagLib::ID3v2::Tag *tag, QWidget *parent) :
    TagEditor(tag, "ID3v2 tag", parent) {

    id3v2Tag = tag;
    genreEdit = new Id3GenreSelection(this);
    int i = genreEdit->findText(QString::fromLocal8Bit(id3v2Tag->genre().toCString()));
    genreEdit->setCurrentIndex(i);
    genreLabel = new QLabel("Genre:", this);
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

    QObject::connect(removeCoverButton, SIGNAL(clicked()), this, SLOT(removeCover()));
    QObject::connect(genreEdit, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTags()));
    QObject::connect(pictureSelection, SIGNAL(pictureChanged()), this, SLOT(updateTags()));
    QObject::connect(extractPictureButton, SIGNAL(clicked(bool)), this, SLOT(savePictureAsFile()));
    QObject::connect(pictureFullSizeButton, SIGNAL(clicked()), this, SLOT(showPictureFullSize()));
    createLayout();

}

Id3v2Editor::~Id3v2Editor() {
    delete picturePath;
}

/*
Overrides TagEditor::createLayout() and adds some ID3v2 specific
widgets to the layout
*/
void Id3v2Editor::createLayout() {

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

    TagEditor::createLayout();
    i = layout->rowCount();
    layout->addWidget(genreLabel, i, 0);
    layout->addWidget(genreEdit, i, 1);

}

/*
 * Overrides TagEditor::updateTags() and updates some ID3v2 specific tags
*/
void Id3v2Editor::updateTags() {

    TagEditor::updateTags();
    id3v2Tag->setGenre(genreEdit->currentText().toStdString());

    if(!picturePath->isEmpty()) {

        TagLib::ID3v2::AttachedPictureFrame* frame = new TagLib::ID3v2::AttachedPictureFrame();
        if(picturePath->endsWith(".jpeg", Qt::CaseInsensitive) || picturePath->endsWith(".jpg", Qt::CaseInsensitive))
            frame->setMimeType("image/jpeg");
        else if(picturePath->endsWith(".png", Qt::CaseInsensitive))
            frame->setMimeType("image/png");
        id3v2Tag->removeFrames("APIC");
        PictureFile pictureFile(picturePath->toStdString().c_str());
        frame->setPicture(pictureFile.getData());
        id3v2Tag->addFrame(frame);

    }

}

void Id3v2Editor::savePictureAsFile() {
    coverArtActions->savePictureAsFile(getPictureFromTag());
}

void Id3v2Editor::showPictureFullSize() {
    coverArtActions->showPictureFullSize(getPictureFromTag());
}

QImage Id3v2Editor::getPictureFromTag() {

    QImage image;
    TagLib::ID3v2::FrameList frameList = id3v2Tag->frameList("APIC");
    if(frameList.isEmpty()) {
        return image;
     }
    TagLib::ID3v2::AttachedPictureFrame *pictureFrame =
        static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frameList.front());
    image.loadFromData((const uchar *) pictureFrame->picture().data(), pictureFrame->picture().size());

    return image;

}

void Id3v2Editor::removeCover() {

    picturePath->clear();
    picturePreview->setPixmap(QPixmap::fromImage(QImage(":images/nofile.png")));
    id3v2Tag->removeFrames("APIC");

}
