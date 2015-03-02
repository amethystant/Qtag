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
#include "tageditorlayout.h"
#include "mainwindow.h"

enum AudioFormat {
    MPEG, OggVorbis, FLAC, WAV, ASF, WavPack
};


/*
A class that represents an opened audio file.
Contains all tags and an editor layout (see TagEditorLayout)
*/
class AudioFile : public QObject {
    Q_OBJECT
public:
    explicit AudioFile(QString path, MainWindow* window);
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
    TagEditorLayout* getEditorLayout();

private:
    TagLib::File* file;
    TagLib::Ogg::XiphComment *xiphComment;
    TagLib::RIFF::Info::Tag *infoTag;
    TagLib::ID3v2::Tag *id3v2;
    TagLib::ID3v1::Tag *id3v1;
    TagLib::ASF::Tag *asfTag;
    TagLib::APE::Tag *apeTag;
    QString path;
    bool hasFileXiphComment;
    bool hasFileId3v1;
    bool hasFileId3v2;
    bool hasFileApeTag;
    bool hasFileAsfTag;
    bool hasFileInfoTag;
    AudioFormat format;
    QString name;
    int track;
    QString album;
    QString artist;
    TagEditorLayout* editorLayout;
    MainWindow* window;

public slots:
    void save();

};

#endif // AUDIOFILE_H
