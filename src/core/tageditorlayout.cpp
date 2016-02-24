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
#include "editors/id3v1editor.h"
#include "editors/id3v2editor.h"
#include "editors/commontageditor.h"
#include "ui_mainwindow.h"

TagEditorLayout::TagEditorLayout(MainWindow *window, AudioFile* file) : QVBoxLayout() {

    edited = false;
    id3v1Tag = NULL;
    id3v2Tag = NULL;
    xiphComment = NULL;
    asfTag = NULL;
    apeTag = NULL;
    infoTag = NULL;
    this->window = window;
    this->file = file;
    parent = window->getUI()->dockWidget_tags;
    loadTagEditors();
    QObject::connect(file, SIGNAL(saved()), this, SLOT(updateSaved()));

}

/*
Determines what method should be called to load the right tag editors to the layout.
*/
void TagEditorLayout::loadTagEditors() {

    if(file->getFormat() == AudioFile::MPEG)
        loadMpegTags();
    else if(file->getFormat() == AudioFile::WavPack)
        loadWavPackTags();
    else if(file->getFormat() == AudioFile::WAV)
        loadWavTags();
    else if(file->getFormat() == AudioFile::FLAC)
        loadFlacTags();
    else if(file->getFormat() == AudioFile::OggVorbis)
        loadOggVorbisTags();
    else if(file->getFormat() == AudioFile::ASF)
        loadAsfTags();

}

void TagEditorLayout::updateEdited() {
    edited = true;
    emit fileEdited();
}

void TagEditorLayout::updateSaved() {
    edited = false;
}

void TagEditorLayout::loadAsfTags() {
    asfTag = file->getAsfTag();
    CommonTagEditor* asfEdit = new CommonTagEditor(asfTag, "ASF tag", parent);
    QObject::connect(asfEdit, SIGNAL(fileEdited()), this, SLOT(updateEdited()));
    addWidget(asfEdit);
}

void TagEditorLayout::loadFlacTags() {
    addId3v1Editor();
    addId3v2Editor();
    addXiphCommentEditor();
}

void TagEditorLayout::loadMpegTags() {
    addId3v1Editor();
    addId3v2Editor();
    addApeTagEditor();
}

void TagEditorLayout::loadOggVorbisTags() {
    addXiphCommentEditor();
}

void TagEditorLayout::loadWavPackTags() {
    addApeTagEditor();
    addId3v1Editor();
}

void TagEditorLayout::loadWavTags() {

    if(file->hasInfoTag()) {
        infoTag = file->getInfoTag();
        CommonTagEditor* infoTagEdit = new CommonTagEditor(infoTag, "Info tag", parent);
        QObject::connect(infoTagEdit, SIGNAL(fileEdited()), this, SLOT(updateEdited()));
        addWidget(infoTagEdit);
    }

    addId3v2Editor();

}

void TagEditorLayout::addId3v1Editor() {
    if(file->hasId3v1()) {
        id3v1Tag = file->getId3v1();
        Id3v1Editor* id3v1Edit = new Id3v1Editor(id3v1Tag, parent);
        QObject::connect(id3v1Edit, SIGNAL(fileEdited()), this, SLOT(updateEdited()));
        addWidget(id3v1Edit);
    }
}

void TagEditorLayout::addId3v2Editor() {
        if(file->hasId3v2()) {
            id3v2Tag = file->getId3v2();
            Id3v2Editor* id3v2Edit = new Id3v2Editor(id3v2Tag, parent);
            QObject::connect(id3v2Edit, SIGNAL(fileEdited()), this, SLOT(updateEdited()));
            addWidget(id3v2Edit);
        }
}

void TagEditorLayout::addApeTagEditor() {
    if(file->hasApeTag()) {
        apeTag = file->getApeTag();
        CommonTagEditor* apeEdit = new CommonTagEditor(apeTag, "APE tag", parent);
        QObject::connect(apeEdit, SIGNAL(fileEdited()), this, SLOT(updateEdited()));
        addWidget(apeEdit);
    }
}

void TagEditorLayout::addXiphCommentEditor() {
    if(file->hasXiphComment()) {
        xiphComment = file->getXiphComment();
        CommonTagEditor* xiphEdit = new CommonTagEditor(xiphComment, "Xiph comment", parent);
        QObject::connect(xiphEdit, SIGNAL(fileEdited()), this, SLOT(updateEdited()));
        addWidget(xiphEdit);
    }
}

AudioFile* TagEditorLayout::getFile() {
    return file;
}

bool TagEditorLayout::isEdited() {
    return edited;
}
