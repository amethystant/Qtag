#include "tageditorlayout.h"

#include "mainwindow.h"
#include "audiofile.h"
#include "id3v1editor.h"
#include "id3v2editor.h"
#include "ui_mainwindow.h"

TagEditorLayout::TagEditorLayout(MainWindow *window, AudioFile* file) : QVBoxLayout() {

   id3v1Tag = NULL;
    id3v2Tag = NULL;
    xiphComment = NULL;
    asfTag = NULL;
    apeTag = NULL;
    infoTag = NULL;
    this->window = window;
    this->file = file;
    loadTagEditors();

}

/*
Determines what method should be called to load the right tag editors to the layout.
*/
void TagEditorLayout::loadTagEditors() {

    if(file->getFormat() == MPEG)
        loadMpegTags();
    else if(file->getFormat() == WavPack)
        loadWavPackTags();
    else if(file->getFormat() == WAV)
        loadWavTags();
    else if(file->getFormat() == FLAC)
        loadFlacTags();
    else if(file->getFormat() == OggVorbis)
        loadOggVorbisTags();
    else if(file->getFormat() == ASF)
        loadAsfTags();

}

void TagEditorLayout::loadAsfTags() {

}

void TagEditorLayout::loadFlacTags() {

}

void TagEditorLayout::loadMpegTags() {

    int i = 0;
    if(file->hasId3v1()) {
        id3v1Tag = file->getId3v1();
        Id3v1Editor* id3v1Edit = new Id3v1Editor(id3v1Tag, window->getUI()->dockWidget_tags);
        addWidget(id3v1Edit);
        i++;
    }

    if(file->hasId3v2()) {
        id3v2Tag = file->getId3v2();
        Id3v2Editor* id3v2Edit = new Id3v2Editor(id3v2Tag, window->getUI()->dockWidget_tags);
        addWidget(id3v2Edit);
        i++;
    }

}

void TagEditorLayout::loadOggVorbisTags() {

}

void TagEditorLayout::loadWavPackTags() {

}

void TagEditorLayout::loadWavTags() {

}

void TagEditorLayout::saveTags() {

}


AudioFile* TagEditorLayout::getFile() {
    return file;
}
