#ifndef TAGEDITOR_H
#define TAGEDITOR_H

#include <QtWidgets>
#include <asftag.h>
#include <id3v1tag.h>
#include <id3v2tag.h>
#include <apetag.h>
#include <infotag.h>
#include <xiphcomment.h>
#include <sstream>
#include "main.h"

class MainWindow;
class AudioFile;

class TagEditorLayout : public QGridLayout {
    Q_OBJECT

public:
    explicit TagEditorLayout(MainWindow* window, AudioFile *file);
    ~TagEditorLayout();
    AudioFile* getFile();

private:
    MainWindow* window;
    AudioFile* file;
    void loadTags();
    void loadAsfTags();
    void loadWavPackTags();
    void loadMpegTags();
    void loadFlacTags();
    void loadWavTags();
    void loadOggVorbisTags();
    TagLib::APE::Tag *apeTag;
    TagLib::ASF::Tag *asfTag;
    TagLib::ID3v1::Tag *id3v1Tag;
    TagLib::ID3v2::Tag *id3v2Tag;
    TagLib::RIFF::Info::Tag *infoTag;
    TagLib::Ogg::XiphComment *xiphComment;
    QList<QGroupBox*> *tagBoxes;

public slots:
    void saveTags();

};

#endif // TAGEDITOR_H
