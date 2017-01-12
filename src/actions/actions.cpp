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

#include <QFile>
#include <QDirIterator>
#include "actions/actions.h"

void Actions::duplicateTags(QList<AudioFile*> *files, TagFormat sourceTag,
                            QList<TagFormat> targetTags, QList<TagKey> listOfKeys, bool coverArt) {

    for(int i = 0; i < files->length(); i++) {

        AudioFile* file = files->at(i);
        AudioTag* source = file->getTagByName(sourceTag);
        if(source == NULL) {
            continue;
        }

        for(int j = 0; j < targetTags.length(); j++) {

            AudioTag* currentTarget = file->getTagByName(targetTags.at(j));
            if(currentTarget == NULL) {
                continue;
            }

            for(int k = 0; k < listOfKeys.length(); k++) {
                TagKey key = listOfKeys.at(k);
                currentTarget->setValue(key, source->getValue(key));
            }

            if(coverArt && source->supportsCoverArt()) {
                QImage* cover = source->getCoverArt();
                if(cover != NULL) {
                    cover->save("cover.png", "PNG");
                    currentTarget->setCoverArt("cover.png");
                    QFile::remove("cover.png");
                }
            }

        }
    }

}

void Actions::writeTagsTo(AudioFile *file,
                          TagFormat format, QList<TagKeyAndValue> listOfValues,
                          bool coverArt, QString coverArtPath) {

    AudioTag* tag = file->getTagByName(format);
    if(tag == NULL) {
        return;
    }

    for(int i = 0; i < listOfValues.length(); i++) {
        tag->setValue(listOfValues.at(i).key, listOfValues.at(i).value);
    }

    if(coverArt) {
        tag->setCoverArt(coverArtPath);
    }

}

void Actions::tagMultipleFiles(QList<AudioFile*> *files, QList<TagFormat> formats,
                               QList<TagKeyAndValue> listOfValues,
                               bool coverArt, QString coverArtPath) {

    for(int i = 0; i < files->length(); i++) {

        AudioFile* file = files->at(i);
        for(int j = 0; j < formats.length(); j++) {

            writeTagsTo(file, formats.at(j), listOfValues, coverArt, coverArtPath);

        }

    }


}

/*
 * Searches the rootDir directory for files that match the specified format and writes tags
 * obtained from the path to them.
 * Returns a list of these files, or NULL if the format is invalid.
 */
QList<AudioFile*>* Actions::createAlbumFromDirectory(FileList* fileList, QString rootDir,
                                      QList<TagFormat> tagFormats, QString tagFormat) {

    QStringList nameFilters;
    QString filter = tagFormat;

    if(filter.count('%') == 0) {
        return NULL;
    }

    while(filter.indexOf('*') != -1 && filter.length() != filter.indexOf('*') + 1) {
        int i = filter.indexOf('*');
        if(filter.at(i + 1) == '%' || filter.at(i + 1) == '?'|| filter.at(i + 1) == '*') {
            return NULL;
        }
    }

    int i = filter.indexOf('?');
    while(i != -1 && filter.length() != i + 1) {

        if(filter.at(i + 1) == '*' || filter.at(i + 1) == '%' || filter.at(i + 1) == '*') {
            return NULL;
        }

        i = filter.indexOf('?', i + 1);

    }

    while(filter.indexOf('%') != -1) {
        int i = filter.indexOf('%');
        if(filter.length() - (i+1) == 1) {
            filter.replace(i, 2, '*');
        } else if(filter.endsWith('%') ||
              ( filter.at(i+1) != 'a' &&
                filter.at(i+1) != 'l' &&
                filter.at(i+1) != 'r' &&
                filter.at(i+1) != 't'    ) ||
                filter.at(i+2) == '*' ||
                filter.at(i+2) == '?' ||
                filter.at(i+2) == '%') {

            return NULL;

        } else {
            filter.replace(i, 2, "*");
        }
    }

    QString nameFilter = filter;
    i = nameFilter.lastIndexOf('/');
    nameFilter.remove(0, i+1);

    nameFilters.append(nameFilter + ".mp3");
    nameFilters.append(nameFilter + ".asf");
    nameFilters.append(nameFilter + ".ogg");
    nameFilters.append(nameFilter + ".wma");
    nameFilters.append(nameFilter + ".flac");
    nameFilters.append(nameFilter + ".wv");
    nameFilters.append(nameFilter + ".wav");
    nameFilters.append(nameFilter + ".wave");

    QDirIterator dirIterator(rootDir, nameFilters, QDir::Files,
                               QDirIterator::Subdirectories);

    QStringList* files = new QStringList();
    while(dirIterator.hasNext()) {
        files->append(dirIterator.next());
    }

    for(i = 0; i < files->length();) {
        QString s = files->at(i);
        s.remove(rootDir + "/");
        if(s.count('/') != filter.count('/')) {
            files->removeAt(i);
        } else {
            i++;
        }
    }

    for(i = 0; i < files->length();) {

        QRegExp r(rootDir + "/" + filter + ".*", Qt::CaseSensitive, QRegExp::Wildcard);
        if(!r.exactMatch(files->at(i))) {
            files->removeAt(i);
        } else {
            i++;
        }

    }

    QList<AudioFile*>* listToReturn = new QList<AudioFile*>();

    if(files->isEmpty()) {
        return listToReturn;
    }

    for(i = 0; i < files->length(); i++) {

        QString path = files->at(i);

        AudioFile* file = fileList->getFileByPath(path);
        if(file == NULL) {
            fileList->addFileToList(path);
            file = fileList->getFileByPath(path);
        }

        listToReturn->append(file);
        QString currentFile = files->at(i);
        currentFile.remove(0, rootDir.length() + 1);
        currentFile.remove(currentFile.lastIndexOf('.'),
                           currentFile.length() - currentFile.lastIndexOf('.'));
        QString title,
                track,
                album,
                artist;
        QString format = tagFormat;
        int loop = format.count('%') + format.count('*') + format.count('?');
        for(int i1 = 0; i1 < loop; i1++) {

            int index = format.indexOf('%');
            int index1 = format.indexOf('*');
            int index2 = format.indexOf('?');
            if((index < index1 || index1 == -1)&&
                    (index < index2 || index2 == -1) && index != -1) {

                QString s = format.section('%', 1, 1);
                QChar symbol  = s.at(0);
                s.remove(0, 1);
                int in;
                if(!s.isEmpty()) {
                    QRegExp r(s, Qt::CaseSensitive, QRegExp::Wildcard);
                    in = r.indexIn(currentFile, index);
                } else
                    in = currentFile.length();
                QString extractedString = currentFile.mid(index, in-index);
                format.replace(format.indexOf('%'), 2, extractedString);
                if(symbol == 'a') {
                    artist = extractedString;
                } else if(symbol == 'l') {
                    album = extractedString;
                } else if(symbol == 'r') {
                    track = extractedString;
                } else if(symbol == 't') {
                    title = extractedString;
                }

            } else if((index1 < index || index == -1) &&
                      (index1 < index2 || index2 == -1) && index1 != -1) {

                QString s = format.section('*', 1, 1);
                int in;
                if(!s.isEmpty()) {
                    QRegExp r(s, Qt::CaseSensitive, QRegExp::Wildcard);
                    in = r.indexIn(currentFile, index1);
                } else
                    in = currentFile.length();
                QString extractedString = currentFile.mid(index1, in-index1);
                format.replace(format.indexOf('*'), 1, extractedString);


            } else if((index2 < index || index == -1) &&
                      (index2 < index1 || index1 == -1) && index2 != -1) {


                QString extractedChar = currentFile.mid(index2, 1);
                format.replace(format.indexOf('?'), 1, extractedChar);

            }

        }

        QList<Actions::TagKeyAndValue> listOfValues;

        TagKeyAndValue value;

        if(!title.isEmpty()) {
            value.key = TagKeys::TITLE;
            value.value = title;
            listOfValues.append(value);
        }
        if(!track.isEmpty()) {
            value.key = TagKeys::TRACK;
            value.value = track;
            listOfValues.append(value);
        }
        if(!album.isEmpty()) {
            value.key = TagKeys::ALBUM;
            value.value = album;
            listOfValues.append(value);
        }
        if(!artist.isEmpty()) {
            value.key = TagKeys::ARTIST;
            value.value = artist;
            listOfValues.append(value);
        }

        for(int j = 0; j < tagFormats.length(); j++) {
            writeTagsTo(file, tagFormats.at(j), listOfValues, false, QString());
        }

    }

    delete files;
    return listToReturn;

}

void Actions::capitalizeTags(AudioFile *file, QList<TagFormat> formats, QList<TagKey> listOfKeys) {

    for(int i = 0; i < formats.length(); i++) {
        AudioTag* tag = file->getTagByName(formats.at(i));
        if(tag == NULL) {
            continue;
        }

        for(int j = 0; j < listOfKeys.length(); j++) {
            TagKey key = listOfKeys.at(j);
            tag->setValue(key, capitalized(tag->getValue(key)));
        }

    }

}

void Actions::replaceStringsInTags(AudioFile *file, QList<TagFormat> formats,
                                   QList<TagKey> listOfKeys, QString replace, QString replaceWith) {

    for(int i = 0; i < formats.length(); i++) {

        AudioTag* tag = file->getTagByName(formats.at(i));
        if(tag == NULL) {
            continue;
        }

        for(int j = 0; j < listOfKeys.length(); j++) {
            TagKey key = listOfKeys.at(j);
            QString value = tag->getValue(key);
            value.replace(replace, replaceWith);
            tag->setValue(key, value);
        }

    }

}
