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

#include "commontageditor.h"

CommonTagEditor::CommonTagEditor(TagLib::Tag *tag, QString nameOfTag, QWidget *parent) :
    TagEditor(tag, nameOfTag, parent) {

    genreEdit = new QLineEdit(this);
    genreEdit->setText(QString::fromLocal8Bit(tag->genre().toCString(true)));
    genreLabel = new QLabel("Genre:", this);

    createLayout();
    QObject::connect(genreEdit, SIGNAL(textEdited(QString)), this, SLOT(updateTags()));

}

/*
 *Overrides TagEditor::saveTags() and updates the genre tag
*/
void CommonTagEditor::updateTags() {

    TagEditor::updateTags();
    tag->setGenre(genreEdit->text().toStdString());

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
