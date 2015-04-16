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
