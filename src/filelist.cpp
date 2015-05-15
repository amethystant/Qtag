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

#include "filelist.h"

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
        AudioFile *newFile = new AudioFile(path, this);
        listOfOpenedFiles.append(newFile);
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
