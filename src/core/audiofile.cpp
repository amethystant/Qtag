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

#include "core/audiofile.h"
#include "core/main.h"
#include <QFile>
#include <audioproperties.h>
#include <tstring.h>

AudioFile::AudioFile(QString path, QObject* parent) : QObject(parent) {

    this->path = path;

    hasFileApeTag = false;
    hasFileAsfTag = false;
    hasFileId3v1 = false;
    hasFileId3v2 = false;
    hasFileXiphComment = false;
    hasFileInfoTag = false;

    xiphComment = NULL;
    id3v1 = NULL;
    id3v2 = NULL;
    apeTag = NULL;
    asfTag = NULL;
    infoTag = NULL;

    open(path);

}

AudioFile::~AudioFile() {
    delete file;
}

/*
This method initializes the tags
*/
void AudioFile::open(QString path) {

    QByteArray encodedFileName = QFile::encodeName(path);
    const char* char_path = encodedFileName.constData();
    TagLib::FileName fileName = char_path;

    TagLib::AudioProperties* properties;

    if(path.endsWith(".mp3", Qt::CaseInsensitive)) {
        format = MPEG;
        TagLib::MPEG::File* f = new TagLib::MPEG::File(fileName);
        properties = f->audioProperties();
        file = f;
        hasFileId3v1 = true;
        hasFileId3v2 = true;
        hasFileApeTag = true;
        id3v1 = f->ID3v1Tag(true);
        id3v2 = f->ID3v2Tag(true);
        apeTag = f->APETag(true);

    } else if(path.endsWith(".flac", Qt::CaseInsensitive)) {

        format = FLAC;
        TagLib::FLAC::File *f = new TagLib::FLAC::File(fileName);
        properties = f->audioProperties();
        file = f;
        hasFileId3v1 = true;
        hasFileId3v2 = true;
        hasFileXiphComment = true;
        id3v1 = f->ID3v1Tag(true);
        id3v2 = f->ID3v2Tag(true);
        xiphComment = f->xiphComment(true);

    } else if(path.endsWith(".wav", Qt::CaseInsensitive) ||
              path.endsWith(".wave", Qt::CaseInsensitive)) {

        format = WAV;
        TagLib::RIFF::WAV::File *f = new TagLib::RIFF::WAV::File(fileName);
        properties = f->audioProperties();
        file = f;
        hasFileId3v2 = true;
        hasFileInfoTag = true;
        id3v2 = f->ID3v2Tag();
        infoTag = f->InfoTag();

    } else if(path.endsWith(".asf", Qt::CaseInsensitive) ||
              path.endsWith(".wma", Qt::CaseInsensitive)) {

        format = ASF;
        hasFileAsfTag = true;
        TagLib::ASF::File *f = new TagLib::ASF::File(fileName);
        properties = f->audioProperties();
        file = f;
        asfTag = f->tag();

    } else if(path.endsWith(".wv", Qt::CaseInsensitive)) {

        format = WavPack;
        TagLib::WavPack::File *f = new TagLib::WavPack::File(fileName);
        properties = f->audioProperties();
        file = f;
        hasFileApeTag = true;
        hasFileId3v1 = true;
        apeTag = f->APETag(true);
        id3v1 = f->ID3v1Tag(true);

    } else if(path.endsWith(".ogg", Qt::CaseInsensitive)) {

        format = OggVorbis;
        hasFileXiphComment = true;
        TagLib::Ogg::Vorbis::File *f = new TagLib::Ogg::Vorbis::File(fileName);
        properties = f->audioProperties();
        file = f;
        xiphComment = f->tag();

    }

#ifndef WIN32
    TagLib::FileRef *f = new TagLib::FileRef(char_path);

    TagLib::Tag *tag = f->tag();
    name = QString::fromStdString(tag->title().to8Bit(true));
    track = tag->track();
    album = QString::fromStdString(tag->album().to8Bit(true));
    artist = QString::fromStdString(tag->artist().to8Bit(true));

    delete f;
#else
    TagLib::Tag *tag;
     if(id3v1 && !id3v1->isEmpty())
         tag = id3v1;
     else if(id3v2 && !id3v2->isEmpty())
         tag = id3v2;
     else if(apeTag && !apeTag->isEmpty())
         tag = apeTag;
     else if(asfTag && !asfTag->isEmpty())
         tag = asfTag;
     else if(xiphComment && !xiphComment->isEmpty())
         tag = xiphComment;
     else if(infoTag && !infoTag->isEmpty())
         tag = infoTag;

     name = QString::fromStdString(tag->title().to8Bit(true));
     track = tag->track();
     album = QString::fromStdString(tag->album().to8Bit(true));
     artist = QString::fromStdString(tag->artist().to8Bit(true));
#endif

    bitrate = properties->bitrate();
    channels = properties->channels();
    length = properties->length();
    sampleRate = properties->sampleRate();

}

/*Saves the tags in the file*/
void AudioFile::save() {

    if(format == MPEG) {
        TagLib::MPEG::File* f = (TagLib::MPEG::File*) file;
        f->save(TagLib::MPEG::File::AllTags, false, 4, false);
    } else {
        file->save();
    }

    updateBasicInfo();
    emit saved();

}

void AudioFile::updateBasicInfo() {

    TagLib::Tag *tag;
    if(id3v1 && !id3v1->isEmpty())
        tag = id3v1;
    else if(id3v2 && !id3v2->isEmpty())
        tag = id3v2;
    else if(apeTag && !apeTag->isEmpty())
        tag = apeTag;
    else if(asfTag && !asfTag->isEmpty())
        tag = asfTag;
    else if(xiphComment && !xiphComment->isEmpty())
        tag = xiphComment;
    else if(infoTag && !infoTag->isEmpty())
        tag = infoTag;

    name = QString::fromStdString(tag->title().to8Bit(true));
    track = tag->track();
    album = QString::fromStdString(tag->album().to8Bit(true));
    artist = QString::fromStdString(tag->artist().to8Bit(true));

}

QString AudioFile::getPath() {
    return path;
}

QString AudioFile::getName() {
    return name;
}

int AudioFile::getTrack() {
    return track;
}

QString AudioFile::getAlbum() {
    return album;
}

QString AudioFile::getArtist() {
    return artist;
}

bool AudioFile::hasApeTag() {
    return hasFileApeTag;
}

bool AudioFile::hasAsfTag() {
    return hasFileAsfTag;
}

bool AudioFile::hasId3v1() {
    return hasFileId3v1;
}

bool AudioFile::hasId3v2() {
    return hasFileId3v2;
}

bool AudioFile::hasInfoTag() {
    return hasFileInfoTag;
}

bool AudioFile::hasXiphComment() {
    return hasFileXiphComment;
}

TagLib::Ogg::XiphComment* AudioFile::getXiphComment() {
    if(hasFileXiphComment)
        return xiphComment;
    return NULL;
}

TagLib::RIFF::Info::Tag* AudioFile::getInfoTag() {
    if(hasFileInfoTag)
        return infoTag;
    return NULL;
}

TagLib::ID3v2::Tag* AudioFile::getId3v2() {
    if(hasFileId3v2)
        return id3v2;
    return NULL;
}

TagLib::ID3v1::Tag* AudioFile::getId3v1() {
    if(hasFileId3v1)
        return id3v1;
    return NULL;
}

TagLib::ASF::Tag* AudioFile::getAsfTag() {
    if(hasFileAsfTag)
        return asfTag;
    return NULL;
}

TagLib::APE::Tag* AudioFile::getApeTag() {
    if(hasFileApeTag)
        return apeTag;
    return NULL;
}

AudioFormat AudioFile::getFormat() {
    return format;
}

/*
 * Returns a pointer to the tag specified by the parameter "name",
 * which must be one of the values in the NamesOfTags namespace
 * (returns NULL if it isn't)
*/
TagLib::Tag* AudioFile::getTagByName(QString name) {
    if(name.compare(QString::fromStdString(NamesOfTags::APE)) == 0)
        return apeTag;
    else if(name.compare(QString::fromStdString(NamesOfTags::ASF)) == 0)
        return asfTag;
    else if(name.compare(QString::fromStdString(NamesOfTags::ID3V1)) == 0)
        return id3v1;
    else if(name.compare(QString::fromStdString(NamesOfTags::ID3V2)) == 0)
        return id3v2;
    else if(name.compare(QString::fromStdString(NamesOfTags::INFO)) == 0)
        return infoTag;
    else if(name.compare(QString::fromStdString(NamesOfTags::XIPH)) == 0)
        return xiphComment;

        return NULL;
}

QString AudioFile::getType() {

    QString returnValue;
    if(format == ASF) {
        returnValue = "ASF";
    } else if(format == WavPack) {
        returnValue = "Wav Pack";
    } else if(format == WAV) {
        returnValue = "WAV";
    } else if(format == OggVorbis) {
        returnValue = "Ogg Vorbis";
    } else if(format == FLAC) {
        returnValue = "FLAC";
    } else if(format == MPEG) {
        returnValue = "MPEG";
    }

    return returnValue;

}

int AudioFile::getBitrate() {
    return bitrate;
}

int AudioFile::getLength() {
    return length;
}

int AudioFile::getChannels() {
    return channels;
}

int AudioFile::getSampleRate() {
    return sampleRate;
}
