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

#ifndef TAGEDITOR_H
#define TAGEDITOR_H

#include <QtWidgets>
#include <tag.h>
#include "main.h"
#include <fileref.h>

/*
The base class for all tag editors (e.g. ID3v1 editor, XiphComment editor,...).
Contains all the common widgets and a method to save the tags
*/

class TagEditor : public QGroupBox {

    Q_OBJECT

public:
    TagEditor(TagLib::Tag* tag, QString nameOfTag, QWidget *parent);

protected:
    TagLib::Tag* tag;
    QGridLayout* layout;
    QLabel* titleLabel;
    QLabel* trackLabel;
    QLabel* albumLabel;
    QLabel* artistLabel;
    QLabel* commentLabel;
    QLabel* yearLabel;
    QLineEdit* titleEdit;
    QLineEdit* trackEdit;
    QLineEdit* albumEdit;
    QLineEdit* artistEdit;
    QLineEdit* commentEdit;
    QLineEdit* yearEdit;
    virtual void createLayout();

protected slots:
    virtual void updateTags();

signals:
    void fileEdited();

};

#endif // TAGEDITOR_H
