#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include <QObject>
#include <QString>
#include <taglib.h>
#include <mpegfile.h>
#include <flacfile.h>
#include <wavfile.h>
#include <vorbisfile.h>
#include <mp4file.h>
#include <asffile.h>
#include <wavpackfile.h>
#include <fileref.h>
#include <id3v1tag.h>
#include <id3v2tag.h>
#include <xiphcomment.h>
#include <asftag.h>
#include <apetag.h>

enum AudioFormat {
    MPEG, MP4, OggVorbis, FLAC, WAV, ASF, WavPack
};

class AudioFile : public QObject {
    Q_OBJECT
public:
    explicit AudioFile(QString path, QObject *parent = 0);
    ~AudioFile();
    void open(QString path);
    QString getPath();
    QString getName();
    int getTrack();
    QString getAlbum();
    QString getArtist();

private:
    QString path;
    bool hasXiphComment;
    bool hasId3v1;
    bool hasId3v2;
    bool hasApeTag;
    bool hasAsfTag;
    bool hasInfoTag;
    bool hasMp4Tag;
    AudioFormat format;
    QString name;
    int track;
    QString album;
    QString artist;


public slots:
    void save();
};

#endif // AUDIOFILE_H
