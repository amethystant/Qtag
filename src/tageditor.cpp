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

#include "tageditor.h"

TagEditor::TagEditor(TagLib::Tag* tag, QString nameOfTag, QWidget *parent) : QGroupBox(nameOfTag, parent) {

    this->tag = tag;
    layout = new QGridLayout(this);

    titleLabel = new QLabel("Title:", this);
    titleEdit = new QLineEdit(this);
    titleEdit->setText(QString::fromUtf8(tag->title().toCString(true)));

    trackLabel = new QLabel("Track:", this);
    trackEdit = new QLineEdit(this);
    trackEdit->setValidator(new QIntValidator(1, 10000, trackEdit));
    trackEdit->setText(intToString(tag->track()));

    albumLabel = new QLabel("Album:", this);
    albumEdit = new QLineEdit(this);
    albumEdit->setText(QString::fromStdString(tag->album().to8Bit(true)));

    yearLabel = new QLabel("Year:", this);
    yearEdit = new QLineEdit(this);
    yearEdit->setValidator(new QIntValidator(0, 10000, yearEdit));
    yearEdit->setText(intToString(tag->year()));

    artistLabel = new QLabel("Artist:", this);
    artistEdit = new QLineEdit(this);
    artistEdit->setText(QString::fromStdString(tag->artist().to8Bit(true)));

    commentLabel = new QLabel("Comment:", this);
    commentEdit = new QLineEdit(this);
    commentEdit->setText(QString::fromStdString(tag->comment().to8Bit(true)));

    QObject::connect(titleEdit, SIGNAL(textEdited(QString)), this, SIGNAL(fileEdited()));
    QObject::connect(trackEdit, SIGNAL(textEdited(QString)), this, SIGNAL(fileEdited()));
    QObject::connect(albumEdit, SIGNAL(textEdited(QString)), this, SIGNAL(fileEdited()));
    QObject::connect(yearEdit, SIGNAL(textEdited(QString)), this, SIGNAL(fileEdited()));
    QObject::connect(artistEdit, SIGNAL(textEdited(QString)), this, SIGNAL(fileEdited()));
    QObject::connect(commentEdit, SIGNAL(textEdited(QString)), this, SIGNAL(fileEdited()));
    QObject::connect(this, SIGNAL(fileEdited()), this, SLOT(updateTags()));

    createLayout();

}

/*
 * A virtual method which updates the tags in the opened file (it does not save them)
 * Called when the user writes something into the editor
*/
void TagEditor::updateTags() {

    tag->setTitle(titleEdit->text().toStdString());
    tag->setTrack(trackEdit->text().toInt());
    tag->setAlbum(albumEdit->text().toStdString());
    tag->setYear(yearEdit->text().toInt());
    tag->setArtist(artistEdit->text().toStdString());
    tag->setComment(commentEdit->text().toStdString());

}

/*
A virtual method which adds all widgets to a layout
*/
void TagEditor::createLayout() {

    int i = layout->rowCount();
    layout->addWidget(titleLabel, i, 0);
    layout->addWidget(titleEdit, i, 1);
    i++;
    layout->addWidget(trackLabel, i, 0);
    layout->addWidget(trackEdit, i, 1);
    i++;
    layout->addWidget(albumLabel, i, 0);
    layout->addWidget(albumEdit, i, 1);
    i++;
    layout->addWidget(yearLabel, i, 0);
    layout->addWidget(yearEdit, i, 1);
    i++;
    layout->addWidget(artistLabel, i, 0);
    layout->addWidget(artistEdit, i, 1);
    i++;
    layout->addWidget(commentLabel, i, 0);
    layout->addWidget(commentEdit, i, 1);
    setLayout(layout);

}
