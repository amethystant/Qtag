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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

namespace Settings {

    enum IconTheme {
        NATIVE, OXYGEN
    };

    void setIconTheme(IconTheme theme);
    void setApplicationTheme(QString theme);
    void setWarnBeforeClosingUnsavedFiles(bool warn);
    void setPicturePreviewSize(int size);
    void setOpenFilesFromLastSession(bool open);

    IconTheme getIconTheme();
    QString getApplicationTheme();
    bool getWarnBeforeClosingUnsavedFiles();
    int getPicturePreviewSize();
    bool getOpenLastSession();

}

#endif // SETTINGS_H
