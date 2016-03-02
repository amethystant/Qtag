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
                            QList<TagFormat> targetTags, MultipleTaggingOptions options) {

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

            if(options.title) {
                currentTarget->setTitle(source->getTitle());
            }
            if(options.track) {
                currentTarget->setTrack(source->getTrack());
            }
            if(options.album) {
                currentTarget->setAlbum(source->getAlbum());
            }
            if(options.artist) {
                currentTarget->setArtist(source->getArtist());
            }
            if(options.genre) {
                currentTarget->setGenre(source->getGenre());
            }
            if(options.comment) {
                currentTarget->setComment(source->getComment());
            }
            if(options.year) {
                currentTarget->setYear(source->getYear());
            }
            if(options.coverArt && source->getFormat() == TagFormats::ID3V2) {
                QImage* cover = source->getCoverArt();
                if(cover != NULL)
                    cover->save("cover.png", "PNG");
                currentTarget->setCoverArt("cover.png");
                QFile::remove("cover.png");
            }

        }
    }

}

void Actions::writeTagsTo(AudioFile *file, MultipleTaggingPattern pattern,
                          TagFormat format, MultipleTaggingOptions options) {

    AudioTag* tag = file->getTagByName(format);
    if(tag == NULL) {
        return;
    }

    if(options.title) {
        tag->setTitle(pattern.title);
    }
    if(options.track) {
        tag->setTrack(pattern.track);
    }
    if(options.album) {
        tag->setAlbum(pattern.album);
    }
    if(options.artist) {
        tag->setArtist(pattern.artist);
    }
    if(options.genre) {
        tag->setGenre(pattern.genre);
    }
    if(options.comment) {
        tag->setComment(pattern.comment);
    }
    if(options.year) {
        tag->setYear(pattern.year);
    }
    if(options.coverArt) {
        tag->setCoverArt(pattern.coverArt);
    }

}

void Actions::tagMultipleFiles(QList<AudioFile*> *files, MultipleTaggingPattern pattern,
                               QList<TagFormat> formats, MultipleTaggingOptions options) {

    for(int i = 0; i < files->length(); i++) {

        AudioFile* file = files->at(i);
        for(int j = 0; j < formats.length(); j++) {

            writeTagsTo(file, pattern, formats.at(j), options);

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

    while(filter.indexOf('?') != -1 && filter.length() != filter.indexOf('?') + 1) {
        int i = filter.indexOf('?');
        if(filter.at(i + 1) == '*' || filter.at(i + 1) == '%' || filter.at(i + 1) == '*') {
            return NULL;
        }
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
    int i = nameFilter.lastIndexOf('/');
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
                if(!s.isEmpty())
                    in = currentFile.indexOf(s, index);
                else
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
                if(!s.isEmpty())
                    in = currentFile.indexOf(s, index1);
                else
                    in = currentFile.length();
                QString extractedString = currentFile.mid(index1, in-index1);
                format.replace(format.indexOf('*'), 1, extractedString);


            } else if((index2 < index || index == -1) &&
                      (index2 < index1 || index1 == -1) && index2 != -1) {


                QString extractedChar = currentFile.mid(index1, 1);
                format.replace(format.indexOf('?'), 1, extractedChar);

            }

        }

        MultipleTaggingOptions options;
        options.comment = false;
        options.coverArt = false;
        options.genre = false;
        options.year = false;
        options.title = false;
        options.track = false;
        options.album = false;
        options.artist = false;

        if(!title.isEmpty())
            options.title = true;
        if(!track.isEmpty())
            options.track = true;
        if(!album.isEmpty())
            options.album = true;
        if(!artist.isEmpty())
            options.artist = true;

        MultipleTaggingPattern pattern;
        pattern.title = title;
        if(track.startsWith('0'))
            track.remove(0, 1);
        pattern.track = track.toInt();
        pattern.album = album;
        pattern.artist = artist;

        for(int j = 0; j < tagFormats.length(); j++) {
            writeTagsTo(file, pattern, tagFormats.at(j), options);
        }

    }

    delete files;
    return listToReturn;

}

void Actions::capitalizeTags(AudioFile *file, QList<TagFormat> formats, MultipleTaggingOptions options) {

    for(int i = 0; i < formats.length(); i++) {
        AudioTag* tag = file->getTagByName(formats.at(i));
        if(tag == NULL) {
            continue;
        }

        if(options.title) {
            tag->setTitle(capitalized(tag->getTitle()));
        }
        if(options.album) {
            tag->setAlbum(capitalized(tag->getAlbum()));
        }
        if(options.artist) {
            tag->setArtist(capitalized(tag->getArtist()));
        }
        if(options.genre) {
            tag->setGenre(capitalized(tag->getGenre()));
        }
        if(options.comment) {
            tag->setComment(capitalized(tag->getComment()));
        }

    }

}

void Actions::replaceStringsInTags(AudioFile *file, QList<TagFormat> formats,
                                   MultipleTaggingOptions options, QString replace, QString replaceWith) {

    for(int i = 0; i < formats.length(); i++) {

        AudioTag* tag = file->getTagByName(formats.at(i));
        if(tag == NULL) {
            continue;
        }

        if(options.title) {
            QString title = tag->getTitle();
            title.replace(replace, replaceWith);
            tag->setTitle(title);
        }
        if(options.album) {
            QString album = tag->getAlbum();
            album.replace(replace, replaceWith);
            tag->setAlbum(album);
        }
        if(options.artist) {
            QString artist = tag->getArtist();
            artist.replace(replace, replaceWith);
            tag->setArtist(artist);
        }
        if(options.genre) {
            QString genre = tag->getGenre();
            genre.replace(replace, replaceWith);
            tag->setGenre(genre);
        }
        if(options.comment) {
            QString comment = tag->getComment();
            comment.replace(replace, replaceWith);
            tag->setComment(comment);
        }

    }

}
