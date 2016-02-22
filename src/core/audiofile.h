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


#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include <QObject>
#include <QString>
#include <taglib.h>
#include <mpegfile.h>
#include <flacfile.h>
#include <wavfile.h>
#include <vorbisfile.h>
#include <asffile.h>
#include <wavpackfile.h>
#include <fileref.h>
#include <id3v1tag.h>
#include <id3v2tag.h>
#include <xiphcomment.h>
#include <asftag.h>
#include <apetag.h>

enum AudioFormat {
    MPEG, OggVorbis, FLAC, WAV, ASF, WavPack
};

typedef union {
    TagLib::ASF::File* asfFile;
    TagLib::FLAC::File* flacFile;
    TagLib::RIFF::WAV::File* wavFile;
    TagLib::WavPack::File* wavPackFile;
    TagLib::MPEG::File* mpegFile;
    TagLib::Ogg::Vorbis::File* vorbisFile;
} File;

class MainWindow;

/*
 * A class that represents an opened audio file.
 * Contains all tags.
*/
class AudioFile : public QObject {
    Q_OBJECT
public:
    explicit AudioFile(QString path, QObject *parent);
    ~AudioFile();
    void open(QString path);
    QString getPath();
    QString getName();
    int getTrack();
    QString getAlbum();
    QString getArtist();
    bool hasApeTag();
    bool hasAsfTag();
    bool hasId3v1();
    bool hasId3v2();
    bool hasInfoTag();
    bool hasXiphComment();
    TagLib::Ogg::XiphComment* getXiphComment();
    TagLib::RIFF::Info::Tag* getInfoTag();
    TagLib::ID3v2::Tag* getId3v2();
    TagLib::ID3v1::Tag* getId3v1();
    TagLib::ASF::Tag* getAsfTag();
    TagLib::APE::Tag* getApeTag();
    AudioFormat getFormat();
    TagLib::Tag* getTagByName(QString name);
    QString getType();
    int getBitrate();
    int getChannels();
    int getSampleRate();
    int getLength();

private:
    File* file;

    /*
    Pointers to all possible tags, the value is NULL if the
    file does not have the tag (e.g. a MPEG file has only id3v1 and id3v2)
    */
    TagLib::Ogg::XiphComment *xiphComment;
    TagLib::RIFF::Info::Tag *infoTag;
    TagLib::ID3v2::Tag *id3v2;
    TagLib::ID3v1::Tag *id3v1;
    TagLib::ASF::Tag *asfTag;
    TagLib::APE::Tag *apeTag;
    
     // the full path to the file
    QString path;
   
      //this booleans indicate if the file has the tag. default value is false
    bool hasFileXiphComment;
    bool hasFileId3v1;
    bool hasFileId3v2;
    bool hasFileApeTag;
    bool hasFileAsfTag;
    bool hasFileInfoTag;
    
    AudioFormat format;
    
    //Some basic info
    QString name;
    int track;
    QString album;
    QString artist;
    int bitrate;
    int channels;
    int length;
    int sampleRate;

    void updateBasicInfo();

public slots:
    void save();

signals:
    void saved();

};

#endif // AUDIOFILE_H
