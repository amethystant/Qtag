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

#ifndef ID3V1EDITOR_H
#define ID3V1EDITOR_H

#include <id3v1tag.h>
#include "editors/assistant_classes/id3genreselection.h"
#include "editors/tageditor.h"

/*
The Id3v1 implementation of TagEditor class
*/
class Id3v1Editor : public TagEditor {

    Q_OBJECT

public:
    Id3v1Editor(TagLib::ID3v1::Tag* tag, QWidget *parent);

private:
    TagLib::ID3v1::Tag* id3v1Tag;
    Id3GenreSelection* genreEdit;
    QLabel* genreLabel;

protected:
    virtual void createLayout();

protected slots:
    virtual void updateTags();
};

#endif // ID3V1EDITOR_H
