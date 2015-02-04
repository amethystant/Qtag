#include "audiofile.h"

AudioFile::AudioFile(QString path, QObject *parent) : QObject(parent) {

    this->path = path;
    hasApeTag = false;
    hasAsfTag = false;
    hasId3v1 = false;
    hasId3v2 = false;
    hasXiphComment = false;
    hasInfoTag = false;
    hasMp4Tag = false;
    open(path);

}

AudioFile::~AudioFile() {

}

void AudioFile::open(QString path) {

    TagLib::FileName fileName = path.toStdString().c_str();
    if(path.endsWith(".mp3", Qt::CaseInsensitive)) {
        format = MPEG;
        TagLib::MPEG::File f(fileName);
        hasId3v1 = f.hasID3v1Tag();
        hasId3v2 = f.hasID3v2Tag();
        hasApeTag = f.hasAPETag();

    } else if(path.endsWith(".flac", Qt::CaseInsensitive)) {

        format = FLAC;
        TagLib::FLAC::File f(fileName);
        hasId3v1 = f.hasID3v1Tag();
        hasId3v2 = f.hasID3v2Tag();
        hasXiphComment = f.hasXiphComment();

    } else if(path.endsWith(".wav", Qt::CaseInsensitive) ||
              path.endsWith(".wave"), Qt::CaseInsensitive) {

        format = WAV;
        TagLib::RIFF::WAV::File f(fileName);
        hasId3v2 = f.hasID3v2Tag();
        hasInfoTag = f.hasInfoTag();

    } else if(path.endsWith(".mp4", Qt::CaseInsensitive)) {

        format = MP4;
        hasMp4Tag = true;

    } else if(path.endsWith(".asf", Qt::CaseInsensitive) ||
              path.endsWith(".wma", Qt::CaseInsensitive)) {

        format = ASF;
        hasAsfTag = true;

    } else if(path.endsWith(".wv", Qt::CaseInsensitive)) {

        format = WavPack;
        TagLib::WavPack::File f(fileName);
        hasApeTag = f.hasAPETag();
        hasId3v1 = f.hasID3v1Tag();

    } else if(path.endsWith(".ogg", Qt::CaseInsensitive)) {

        format = OggVorbis;
        hasXiphComment = true;

    }

    TagLib::FileRef f(path.toStdString().c_str());
    TagLib::Tag *tag = f.tag();
    name = QString::fromStdString(tag->title().to8Bit(true));
    track = tag->track();
    album = QString::fromStdString(tag->album().to8Bit(true));
    artist = QString::fromStdString(tag->artist().to8Bit(true));

}

void AudioFile::save() {

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
