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

#ifndef FILELIST_H
#define FILELIST_H

#include <QObject>
#include <QList>
#include <QStringList>
#include "core/audiofile.h"

class FileList : public QObject {

    Q_OBJECT

public:
    explicit FileList(QObject *parent, QStringList *listOfFiles = NULL);
    AudioFile* at(int index);
    AudioFile* getFileByPath(QString path);
    int length();
    bool isEmpty();
    int indexOf(AudioFile* f);
    void addFileToList(QString path);
    void closeFile(QString path);
    void closeFile(int i);
    bool isFileOpened(QString path);

private:
    QList<AudioFile*> listOfOpenedFiles;

signals:
    void fileListChanged();

};

#endif // FILELIST_H
