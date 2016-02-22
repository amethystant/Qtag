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

#ifndef MAIN_H
#define MAIN_H

/*
This file declares some simple non-objected functions and variables
*/

#include <QString>
#include <QApplication>
#include <QStyle>
#include <QSettings>
#include <QVariant>
#include <string>

QString intToString(int i);
QString capitalized(QString s);


const std::string NAME_FILTER = "Audio files (*.mp3 *.wav *.wave *.flac *.ogg *.wma *.asf *.wv)";
const std::string VERSION = "0.1.2";

namespace NamesOfTags {

    const std::string APE = "APE tag";
    const std::string ID3V1= "ID3v1 tag";
    const std::string ID3V2= "ID3v2 tag";
    const std::string ASF= "ASF tag";
    const std::string XIPH= "Xiph Comment";
    const std::string INFO= "RIFF Info tag";

}

QStyle* getStyleFromSettings();

#endif // MAIN_H

