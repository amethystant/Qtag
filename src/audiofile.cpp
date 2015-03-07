#include "audiofile.h"
#include "mainwindow.h"

AudioFile::AudioFile(QString path, MainWindow *window) : QObject(window) {

    this->path = path;
    this->window = window;

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

    delete apeTag;
    delete asfTag;
    delete infoTag;
    delete xiphComment;
    delete id3v1;
    delete id3v2;
    delete file;

}

/*
This method initializes the tags
*/
void AudioFile::open(QString path) {

    TagLib::FileName fileName = path.toStdString().c_str();
    if(path.endsWith(".mp3", Qt::CaseInsensitive)) {
        format = MPEG;
        TagLib::MPEG::File* f = new TagLib::MPEG::File(fileName);
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
        file = f;
        hasFileId3v1 = true;
        hasFileId3v2 = true;
        hasFileXiphComment = true;
        id3v1 = f->ID3v1Tag(true);
        id3v2 = f->ID3v2Tag(true);
        xiphComment = f->xiphComment(true);

    } else if(path.endsWith(".wav", Qt::CaseInsensitive) ||
              path.endsWith(".wave"), Qt::CaseInsensitive) {

        format = WAV;
        TagLib::RIFF::WAV::File *f = new TagLib::RIFF::WAV::File(fileName);
        file = f;
        hasFileId3v2 = f->hasID3v2Tag();
        hasFileInfoTag = f->hasInfoTag();
        if(hasFileId3v2)
            id3v2 = f->ID3v2Tag();
        if(hasFileInfoTag)
            infoTag = f->InfoTag();

    } else if(path.endsWith(".asf", Qt::CaseInsensitive) ||
              path.endsWith(".wma", Qt::CaseInsensitive)) {

        format = ASF;
        hasFileAsfTag = true;
        TagLib::ASF::File *f = new TagLib::ASF::File(fileName);
        file = f;
        asfTag = f->tag();

    } else if(path.endsWith(".wv", Qt::CaseInsensitive)) {

        format = WavPack;
        TagLib::WavPack::File *f = new TagLib::WavPack::File(fileName);
        file = f;
        hasFileApeTag = true;
        hasFileId3v1 = true;
        apeTag = f->APETag(true);
        id3v1 = f->ID3v1Tag(true);

    } else if(path.endsWith(".ogg", Qt::CaseInsensitive)) {

        format = OggVorbis;
        hasFileXiphComment = true;
        TagLib::Ogg::Vorbis::File *f = new TagLib::Ogg::Vorbis::File(fileName);
        file = f;
        xiphComment = f->tag();

    }

    TagLib::FileRef f(path.toStdString().c_str());
    TagLib::Tag *tag = f.tag();
    name = QString::fromStdString(tag->title().to8Bit(true));
    track = tag->track();
    album = QString::fromStdString(tag->album().to8Bit(true));
    artist = QString::fromStdString(tag->artist().to8Bit(true));

}

/*Saves the tags in the file*/
void AudioFile::save() {
    file->save();
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
