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

#include "settings.h"
#include <QSettings>

void Settings::setIconTheme(IconTheme theme){

    QSettings settings;
    switch(theme) {
    case NATIVE:
        settings.setValue("icons", "native");
        break;
    case OXYGEN:
        settings.setValue("icons", "oxygen");
    }

    settings.sync();

}

void Settings::setApplicationTheme(QString theme) {

    QSettings settings;
    settings.setValue("style", theme);
    settings.sync();
}

void Settings::setWarnBeforeClosingUnsavedFiles(bool warn) {
    QSettings settings;
    settings.setValue("warnbeforeclosing", warn);
    settings.sync();
}

void Settings::setPicturePreviewSize(int size) {
    QSettings settings;
    settings.setValue("previewsize", size);
    settings.sync();
}

void Settings::setOpenFilesFromLastSession(bool open) {
    QSettings settings;
    settings.setValue("openfiles", open);
    settings.sync();
}

Settings::IconTheme Settings::getIconTheme() {
    QSettings settings;
    if(settings.value("icons", "native").toString() == QString("oxygen")) {
        return OXYGEN;
    } else {
        return NATIVE;
    }
}

QString Settings::getApplicationTheme() {
    QSettings settings;
    return settings.value("style", "Native").toString();
}

bool Settings::getWarnBeforeClosingUnsavedFiles() {
    QSettings settings;
    return settings.value("warnbeforeclosing", true).toBool();
}

int Settings::getPicturePreviewSize() {
    QSettings settings;
    return settings.value("previewsize", 150).toInt();
}

bool Settings::getOpenLastSession() {
    QSettings settings;
    return settings.value("openfiles", true).toBool();
}
