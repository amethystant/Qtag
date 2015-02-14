#include "tageditorlayout.h"

#include "mainwindow.h"
#include "audiofile.h"

TagEditorLayout::TagEditorLayout(MainWindow *window, AudioFile* file) : QGridLayout(window) {

    id3v1Tag = NULL;
    id3v2Tag = NULL;
    xiphComment = NULL;
    asfTag = NULL;
    apeTag = NULL;
    infoTag = NULL;
    this->window = window;
    this->file = file;
    tagBoxes = new QList<QGroupBox*>();
    loadTags();

}

TagEditorLayout::~TagEditorLayout() {
    delete tagBoxes;
}

/*
Determines what method should be called to load the right tag editors to the layout.
*/
void TagEditorLayout::loadTags() {

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
    QGroupBox* asfTagBox = new QGroupBox(window);

    QLabel* titleLabel = new QLabel("Title:", asfTagBox);
    QLineEdit* titleEditor = new QLineEdit(asfTagBox);
    titleEditor->setText(QString::fromStdString(asfTag->title().to8Bit(true)));

    QLabel* trackLabel = new QLabel("Track:", asfTagBox);
    QLineEdit* trackEditor = new QLineEdit(asfTagBox);
    trackEditor->setValidator(new QIntValidator(1, 10000, window));
    trackEditor->setText(intToString(asfTag->track()));

    QLabel* albumLabel = new QLabel("Album:", asfTagBox);
    QLineEdit* albumEditor = new QLineEdit(asfTagBox);
    albumEditor->setText(QString::fromStdString(asfTag->album().to8Bit(true)));

    QLabel* yearLabel = new QLabel("Year:", asfTagBox);
    QLineEdit* yearEditor = new QLineEdit(asfTagBox);
    yearEditor->setValidator(new QIntValidator(0, 10000, window));
    yearEditor->setText(intToString(asfTag->year()));

    QLabel* artistLabel = new QLabel("Artist:", asfTagBox);
    QLineEdit* artistEditor = new QLineEdit(asfTagBox);
    artistEditor->setText(QString::fromStdString(asfTag->artist().to8Bit(true)));

    QLabel* genreLabel = new QLabel("Genre:", asfTagBox);
    QLineEdit* genreEditor = new QLineEdit(asfTagBox);
    genreEditor->setText(QString::fromStdString(asfTag->genre().to8Bit(true)));

    QLabel* commentLabel = new QLabel("Comment:", asfTagBox);
    QLineEdit* commentEditor = new QLineEdit(asfTagBox);
    commentEditor->setText(QString::fromStdString(asfTag->comment().to8Bit(true)));

    QPushButton* saveButton = new QPushButton("Save tags", asfTagBox);
    QObject::connect(saveButton, SIGNAL(clicked()), this, SLOT(saveTags()));

    int i = 0;
    addWidget(titleLabel, i, 0);
    addWidget(titleEditor, i, 1);
    i++;
    addWidget(trackLabel, i, 0);
    addWidget(trackEditor, i, 1);
    i++;
    addWidget(albumLabel, i, 0);
    addWidget(albumEditor, i, 1);
    i++;
    addWidget(yearLabel, i, 0);
    addWidget(yearEditor, i, 1);
    i++;
    addWidget(artistLabel, i, 0);
    addWidget(artistEditor, i, 1);
    i++;
    addWidget(genreLabel, i, 0);
    addWidget(genreEditor, i, 1);
    i++;
    addWidget(commentLabel, i, 0);
    addWidget(commentEditor, i, 1);

}

void TagEditorLayout::loadFlacTags() {

}

void TagEditorLayout::loadMpegTags() {

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
