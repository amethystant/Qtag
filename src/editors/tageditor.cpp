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


#include "editors/tageditor.h"
#include <tstring.h>

TagEditor::TagEditor(AudioTag *tag, QString nameOfTag, QWidget *parent) : QGroupBox(nameOfTag, parent) {

    this->tag = tag;
    layout = new QGridLayout(this);

    titleLabel = new QLabel("Title:", this);
    titleEdit = new QLineEdit(this);
    titleEdit->setText(tag->getTitle());

    trackLabel = new QLabel("Track:", this);
    trackEdit = new QLineEdit(this);
    trackEdit->setValidator(new QIntValidator(1, 10000, trackEdit));
    trackEdit->setText(intToString(tag->getTrack()));

    albumLabel = new QLabel("Album:", this);
    albumEdit = new QLineEdit(this);
    albumEdit->setText(tag->getAlbum());

    yearLabel = new QLabel("Year:", this);
    yearEdit = new QLineEdit(this);
    yearEdit->setValidator(new QIntValidator(0, 10000, yearEdit));
    yearEdit->setText(intToString(tag->getYear()));

    artistLabel = new QLabel("Artist:", this);
    artistEdit = new QLineEdit(this);
    artistEdit->setText(tag->getArtist());

    commentLabel = new QLabel("Comment:", this);
    commentEdit = new QLineEdit(this);
    commentEdit->setText(tag->getComment());

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

    tag->setTitle(titleEdit->text());
    tag->setTrack(trackEdit->text().toInt());
    tag->setAlbum(albumEdit->text());
    tag->setYear(yearEdit->text().toInt());
    tag->setArtist(artistEdit->text());
    tag->setComment(commentEdit->text());

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
