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

#include "tageditorlayout.h"

#include "core/mainwindow.h"
#include "core/audiofile.h"
#include "editors/tageditorwidget.h"
#include "ui_mainwindow.h"

TagEditorLayout::TagEditorLayout(MainWindow *window, AudioFile* file) : QVBoxLayout() {

    this->window = window;
    this->file = file;
    parent = window->getUI()->dockWidget_tags;
    loadTagEditors();

}

void TagEditorLayout::loadTagEditors() {

    if(file->hasId3v1()) {
        TagEditorWidget* id3v1Edit =
                new TagEditorWidget(file->getId3v1(), QString(TagFormats::ID3V1.c_str()), parent);
        addWidget(id3v1Edit);
    }
    if(file->hasId3v2()) {
        TagEditorWidget* id3v2Edit =
                new TagEditorWidget(file->getId3v2(), QString(TagFormats::ID3V2.c_str()), parent);
        addWidget(id3v2Edit);
    }
    if(file->hasApeTag()) {
        TagEditorWidget* apeEdit =
                new TagEditorWidget(file->getApeTag(), QString(TagFormats::APE.c_str()), parent);
        addWidget(apeEdit);
    }
    if(file->hasAsfTag()) {
        TagEditorWidget* asfEdit =
                new TagEditorWidget(file->getAsfTag(), QString(TagFormats::ASF.c_str()), parent);
        addWidget(asfEdit);
    }
    if(file->hasInfoTag()) {
        TagEditorWidget* infoEdit =
                new TagEditorWidget(file->getInfoTag(), QString(TagFormats::INFO.c_str()), parent);
        addWidget(infoEdit);
    }
    if(file->hasXiphComment()) {
        TagEditorWidget* xiphEdit =
                new TagEditorWidget(file->getXiphComment(), QString(TagFormats::XIPH.c_str()), parent);
        addWidget(xiphEdit);
    }

}

AudioFile* TagEditorLayout::getFile() {
    return file;
}
