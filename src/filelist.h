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

#ifndef FILELIST_H
#define FILELIST_H

#include <QObject>
#include <QList>
#include <QStringList>
#include "audiofile.h"

class FileList : public QObject {

    Q_OBJECT

public:
    explicit FileList(QObject *parent, QStringList *listOfFiles = NULL);
    AudioFile* at(int index);
    AudioFile* closed_at(int inedex);
    AudioFile* getFileByPath(QString path);
    int length();
    int closed_length();
    bool isEmpty();
    bool closed_isEmpty();
    int indexOf(AudioFile* f);
    int closed_indexOf(AudioFile* f);
    void addFileToList(QString path);
    void closeFile(QString path);
    void closeFile(int i);
    bool isFileOpened(QString path);
    bool isFileClosed(QString path);

private:
    QList<AudioFile*> listOfOpenedFiles;
    QList<AudioFile*> listOfClosedFiles;

};

#endif // FILELIST_H
