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

    edited = false;

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
        id3v1 = new AudioTag(this, f->ID3v1Tag(true), TagFormats::ID3V1);
        id3v2 = new AudioTag(this, f->ID3v2Tag(true), TagFormats::ID3V2);
        apeTag = new AudioTag(this, f->APETag(true), TagFormats::APE);

        QObject::connect(id3v1, SIGNAL(edited()), this, SLOT(updateEdited()));
        QObject::connect(id3v2, SIGNAL(edited()), this, SLOT(updateEdited()));
        QObject::connect(apeTag, SIGNAL(edited()), this, SLOT(updateEdited()));

    } else if(path.endsWith(".flac", Qt::CaseInsensitive)) {

        format = FLAC;
        TagLib::FLAC::File *f = new TagLib::FLAC::File(fileName);
        properties = f->audioProperties();
        file = f;
        hasFileId3v1 = true;
        hasFileId3v2 = true;
        hasFileXiphComment = true;
        id3v1 = new AudioTag(this, f->ID3v1Tag(true), TagFormats::ID3V1);
        id3v2 = new AudioTag(this, f->ID3v2Tag(true), TagFormats::ID3V2);
        xiphComment = new AudioTag(this, f->xiphComment(true), TagFormats::XIPH);

        QObject::connect(id3v1, SIGNAL(edited()), this, SLOT(updateEdited()));
        QObject::connect(id3v2, SIGNAL(edited()), this, SLOT(updateEdited()));
        QObject::connect(xiphComment, SIGNAL(edited()), this, SLOT(updateEdited()));

    } else if(path.endsWith(".wav", Qt::CaseInsensitive) ||
              path.endsWith(".wave", Qt::CaseInsensitive)) {

        format = WAV;
        TagLib::RIFF::WAV::File *f = new TagLib::RIFF::WAV::File(fileName);
        properties = f->audioProperties();
        file = f;
        hasFileId3v2 = true;
        hasFileInfoTag = true;
        id3v2 = new AudioTag(this, f->ID3v2Tag(), TagFormats::ID3V2);
        infoTag = new AudioTag(this, f->InfoTag(), TagFormats::INFO);

        QObject::connect(id3v2, SIGNAL(edited()), this, SLOT(updateEdited()));
        QObject::connect(infoTag, SIGNAL(edited()), this, SLOT(updateEdited()));

    } else if(path.endsWith(".asf", Qt::CaseInsensitive) ||
              path.endsWith(".wma", Qt::CaseInsensitive)) {

        format = ASF;
        hasFileAsfTag = true;
        TagLib::ASF::File *f = new TagLib::ASF::File(fileName);
        properties = f->audioProperties();
        file = f;
        asfTag = new AudioTag(this, f->tag(), TagFormats::ASF);

        QObject::connect(asfTag, SIGNAL(edited()), this, SLOT(updateEdited()));

    } else if(path.endsWith(".wv", Qt::CaseInsensitive)) {

        format = WavPack;
        TagLib::WavPack::File *f = new TagLib::WavPack::File(fileName);
        properties = f->audioProperties();
        file = f;
        hasFileApeTag = true;
        hasFileId3v1 = true;
        apeTag = new AudioTag(this, f->APETag(true), TagFormats::APE);
        id3v1 = new AudioTag(this, f->ID3v1Tag(true), TagFormats::ID3V1);

        QObject::connect(apeTag, SIGNAL(edited()), this, SLOT(updateEdited()));
        QObject::connect(id3v1, SIGNAL(edited()), this, SLOT(updateEdited()));

    } else if(path.endsWith(".ogg", Qt::CaseInsensitive)) {

        format = OggVorbis;
        hasFileXiphComment = true;
        TagLib::Ogg::Vorbis::File *f = new TagLib::Ogg::Vorbis::File(fileName);
        properties = f->audioProperties();
        file = f;
        xiphComment = new AudioTag(this, f->tag(), TagFormats::XIPH);

        QObject::connect(xiphComment, SIGNAL(edited()), this, SLOT(updateEdited()));

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
    AudioTag *tag;
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

    name = tag->getTitle();
    track = tag->getTrack();
    album = tag->getAlbum();
    artist = tag->getArtist();
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
    edited = false;
    emit editedOrSaved();

}

void AudioFile::updateBasicInfo() {

    AudioTag *tag;
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
    else {
        name = "";
        track = 0;
        album = "";
        artist = "";
        return;
    }

    name = tag->getTitle();
    track = tag->getTrack();
    album = tag->getAlbum();
    artist = tag->getArtist();

}

void AudioFile::updateEdited() {
    edited = true;
    emit editedOrSaved();
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

AudioTag *AudioFile::getXiphComment() {
    if(hasFileXiphComment)
        return xiphComment;
    return NULL;
}

AudioTag* AudioFile::getInfoTag() {
    if(hasFileInfoTag)
        return infoTag;
    return NULL;
}

AudioTag* AudioFile::getId3v2() {
    if(hasFileId3v2)
        return id3v2;
    return NULL;
}

AudioTag* AudioFile::getId3v1() {
    if(hasFileId3v1)
        return id3v1;
    return NULL;
}

AudioTag* AudioFile::getAsfTag() {
    if(hasFileAsfTag)
        return asfTag;
    return NULL;
}

AudioTag *AudioFile::getApeTag() {
    if(hasFileApeTag)
        return apeTag;
    return NULL;
}

AudioFile::AudioFormat AudioFile::getFormat() {
    return format;
}

/*
 * Returns a pointer to the tag specified by the parameter "name",
 * which must be one of the values in the TagFormats namespace
 * (returns NULL if it isn't)
*/
AudioTag *AudioFile::getTagByName(TagFormat name) {
    if(name == TagFormats::APE)
        return apeTag;
    else if(name == TagFormats::ASF)
        return asfTag;
    else if(name == TagFormats::ID3V1)
        return id3v1;
    else if(name == TagFormats::ID3V2)
        return id3v2;
    else if(name == TagFormats::INFO)
        return infoTag;
    else if(name == TagFormats::XIPH)
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

bool AudioFile::isEdited() {
    return edited;
}
