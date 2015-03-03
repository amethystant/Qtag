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

class MainWindow;

/*
 * A class that represents an opened audio file.
 * Contains all tags.
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

private:
    TagLib::File* file; //this is a pointer to a specific TagLib::File derived object which holds all the TagLib::Tag derived objects

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
    
    //Pointer to the main window
    MainWindow* window;

public slots:
    void save();

};

#endif // AUDIOFILE_H
