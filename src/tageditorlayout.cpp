#include "tageditorlayout.h"

#include "mainwindow.h"
#include "audiofile.h"
#include "id3v1editor.h"
#include "id3v2editor.h"
#include "commontageditor.h"
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
    parent = window->getUI()->dockWidget_tags;
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
    asfTag = file->getAsfTag();
    CommonTagEditor* asfEdit = new CommonTagEditor(asfTag, "ASF tag", parent);
    QObject::connect(asfEdit, SIGNAL(fileEdited()), this, SIGNAL(fileEdited()));
    addWidget(asfEdit);
}

void TagEditorLayout::loadFlacTags() {
    addId3v1Editor();
    addId3v2Editor();
    addXiphCommentEditor();
}

void TagEditorLayout::loadMpegTags() {
    addId3v1Editor();
    addId3v2Editor();
    addApeTagEditor();
}

void TagEditorLayout::loadOggVorbisTags() {
    addXiphCommentEditor();
}

void TagEditorLayout::loadWavPackTags() {
    addApeTagEditor();
    addId3v1Editor();
}

void TagEditorLayout::loadWavTags() {

    if(file->hasInfoTag()) {
        infoTag = file->getInfoTag();
        CommonTagEditor* infoTagEdit = new CommonTagEditor(infoTag, "Info tag", parent);
        QObject::connect(infoTagEdit, SIGNAL(fileEdited()), this, SIGNAL(fileEdited()));
        addWidget(infoTagEdit);
    }

    addId3v2Editor();

}

void TagEditorLayout::addId3v1Editor() {
    if(file->hasId3v1()) {
        id3v1Tag = file->getId3v1();
        Id3v1Editor* id3v1Edit = new Id3v1Editor(id3v1Tag, parent);
        QObject::connect(id3v1Edit, SIGNAL(fileEdited()), this, SIGNAL(fileEdited()));
        addWidget(id3v1Edit);
    }
}

void TagEditorLayout::addId3v2Editor() {
        if(file->hasId3v2()) {
            id3v2Tag = file->getId3v2();
            Id3v2Editor* id3v2Edit = new Id3v2Editor(id3v2Tag, parent);
            QObject::connect(id3v2Edit, SIGNAL(fileEdited()), this, SIGNAL(fileEdited()));
            addWidget(id3v2Edit);
        }
}

void TagEditorLayout::addApeTagEditor() {
    if(file->hasApeTag()) {
        apeTag = file->getApeTag();
        CommonTagEditor* apeEdit = new CommonTagEditor(apeTag, "APE tag", parent);
        QObject::connect(apeEdit, SIGNAL(fileEdited()), this, SIGNAL(fileEdited()));
        addWidget(apeEdit);
    }
}

void TagEditorLayout::addXiphCommentEditor() {
    if(file->hasXiphComment()) {
        xiphComment = file->getXiphComment();
        CommonTagEditor* xiphEdit = new CommonTagEditor(xiphComment, "Xiph comment", parent);
        QObject::connect(xiphEdit, SIGNAL(fileEdited()), this, SIGNAL(fileEdited()));
        addWidget(xiphEdit);
    }
}

AudioFile* TagEditorLayout::getFile() {
    return file;
}
