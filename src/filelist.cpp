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

#include "filelist.h"
#include <QFile>

FileList::FileList(QObject *parent, QStringList *listOfFiles) : QObject(parent) {

    if(listOfFiles != NULL) {
        for(int i = 0; i < listOfFiles->length(); i++) {
            addFileToList(listOfFiles->at(i));
        }
    }

}

AudioFile* FileList::at(int index) {
    return listOfOpenedFiles.at(index);
}

AudioFile* FileList::closed_at(int index) {
    return listOfClosedFiles.at(index);
}

AudioFile* FileList::getFileByPath(QString path) {

    for(int i = 0; i < length(); i++) {

        AudioFile* currentFile = at(i);
        if(currentFile->getPath() == path) {
            return currentFile;
        }

    }

    return NULL;

}

int FileList::length() {
    return listOfOpenedFiles.length();
}

int FileList::closed_length() {
    return listOfClosedFiles.length();
}

bool FileList::isEmpty() {
    return listOfOpenedFiles.isEmpty();
}

bool FileList::closed_isEmpty() {
    return listOfClosedFiles.isEmpty();
}

int FileList::indexOf(AudioFile *f) {
    return listOfOpenedFiles.indexOf(f);
}

int FileList::closed_indexOf(AudioFile *f) {
    return listOfClosedFiles.indexOf(f);
}

void FileList::addFileToList(QString path) {
    if(isFileClosed(path)) {
        for(int i = 0; i < listOfClosedFiles.length(); i++) {
            AudioFile* closedFile = listOfClosedFiles.at(i);
            if(closedFile->getPath() == path) {
                listOfOpenedFiles.append(closedFile);
                listOfClosedFiles.removeAt(i);
                i = listOfClosedFiles.length();
            }
        }
    } else if(!isFileOpened(path)) {
        QFile f(path);
        if(f.exists()) {
            AudioFile *newFile = new AudioFile(path, this);
            listOfOpenedFiles.append(newFile);
        }
    }
}

void FileList::closeFile(int i) {
    AudioFile* f = listOfOpenedFiles.at(i);
    listOfClosedFiles.append(f);
    listOfOpenedFiles.removeOne(f);
}

void FileList::closeFile(QString path) {

    for(int i = 0; i < listOfOpenedFiles.length(); i++) {
        if(listOfOpenedFiles.at(i)->getPath() == path) {
            closeFile(i);
        }
    }

}

bool FileList::isFileOpened(QString path) {
    for(int i = 0; i < listOfOpenedFiles.length(); i++) {
        if(path.compare(listOfOpenedFiles.at(i)->getPath()) == 0)
            return true;
    }
    return false;
}

bool FileList::isFileClosed(QString path) {
    for(int i = 0; i < listOfClosedFiles.length(); i++) {
        if(path == listOfClosedFiles.at(i)->getPath())
            return true;
    }
    return false;
}
