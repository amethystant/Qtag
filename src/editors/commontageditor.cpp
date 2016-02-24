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
    TagEditor(tag, nameOfTag, parent) {

    genreEdit = new QLineEdit(this);
    genreEdit->setText(tag->getGenre());
    genreLabel = new QLabel("Genre:", this);

    createLayout();
    QObject::connect(genreEdit, SIGNAL(textEdited(QString)), this, SLOT(updateTags()));

}

/*
 *Overrides TagEditor::saveTags() and updates the genre tag
*/
void CommonTagEditor::updateTags() {

    TagEditor::updateTags();
    tag->setGenre(genreEdit->text());

}

/*
 *Overrides TagEditor::createLayout() and adds the genre editor
 *to the layout
*/
void CommonTagEditor::createLayout() {

    TagEditor::createLayout();
    int i = layout->rowCount();
    layout->addWidget(genreLabel, i, 0);
    layout->addWidget(genreEdit, i, 1);

}
