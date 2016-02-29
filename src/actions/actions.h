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

#ifndef ACTIONS_H
#define ACTIONS_H

#include <QList>
#include "core/main.h"
#include "core/audiofile.h"
#include "core/filelist.h"

namespace Actions {

    typedef struct {

        bool title;
        bool track ;
        bool album ;
        bool artist ;
        bool genre ;
        bool year;
        bool comment;
        bool coverArt;

    } MultipleTaggingOptions;

    typedef struct {

        QString title;
        int track;
        QString album;
        QString artist;
        QString genre;
        QString comment;
        int year;
        QString coverArt;

    } MultipleTaggingPattern;

    void duplicateTags(QList<AudioFile*> *files, TagFormat sourceTag,
                       QList<TagFormat> targetTags, MultipleTaggingOptions options);

    QList<AudioFile*>* createAlbumFromDirectory(FileList* fileList, QString rootDir,
                                 QList<TagFormat> tagFormats, QString tagFormat);

    void writeTagsTo(AudioFile* file, MultipleTaggingPattern pattern,
                     TagFormat format, MultipleTaggingOptions options);

    void tagMultipleFiles(QList<AudioFile*> *files, MultipleTaggingPattern pattern,
                          QList<TagFormat> formats, MultipleTaggingOptions options);

    void capitalizeTags(AudioFile* file, QList<TagFormat> formats, MultipleTaggingOptions options);

    void replaceStringsInTags(AudioFile* file, QList<TagFormat> formats,
                              MultipleTaggingOptions options, QString replace, QString replaceWith);

}

#endif // ACTIONS_H

