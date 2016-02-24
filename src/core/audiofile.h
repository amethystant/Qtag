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
#include "core/audiotag.h"

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

    enum AudioFormat {
        MPEG, OggVorbis, FLAC, WAV, ASF, WavPack
    };

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
    AudioTag* getXiphComment();
    AudioTag* getInfoTag();
    AudioTag* getId3v2();
    AudioTag* getId3v1();
    AudioTag* getAsfTag();
    AudioTag* getApeTag();
    AudioFormat getFormat();
    AudioTag* getTagByName(TagFormat name);
    QString getType();
    int getBitrate();
    int getChannels();
    int getSampleRate();
    int getLength();

private:
    TagLib::File* file;

    /*
     * Pointers to all possible tags, the value is NULL if the
     * file does not have the tag (e.g. a MPEG file has only id3v1 and id3v2)
     */
    AudioTag* xiphComment;
    AudioTag* infoTag;
    AudioTag* id3v2;
    AudioTag* id3v1;
    AudioTag* asfTag;
    AudioTag* apeTag;

    QString path;
   
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
