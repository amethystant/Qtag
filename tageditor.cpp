#include "tageditor.h"

TagEditor::TagEditor(TagLib::Tag* tag, QString nameOfTag, QWidget *parent) {

    this->tag = tag;
    editorBox = new QGroupBox(parent);
    editorBox->setTitle(nameOfTag);
    layout = new QGridLayout(editorBox);

    titleLabel = new QLabel("Title:", editorBox);
    titleEdit = new QLineEdit(editorBox);
    titleEdit->setText(QString::fromStdString(tag->title().to8Bit(true)));

    trackLabel = new QLabel("Track:", editorBox);
    trackEdit = new QLineEdit(editorBox);
    trackEdit->setValidator(new QIntValidator(1, 10000, trackEdit));
    trackEdit->setText(intToString(tag->track()));

    albumLabel = new QLabel("Album:", editorBox);
    albumEdit = new QLineEdit(editorBox);
    albumEdit->setText(QString::fromStdString(tag->album().to8Bit(true)));

    yearLabel = new QLabel("Year:", editorBox);
    yearEdit = new QLineEdit(editorBox);
    yearEdit->setValidator(new QIntValidator(0, 10000, yearEdit));
    yearEdit->setText(intToString(tag->year()));

    artistLabel = new QLabel("Artist:", editorBox);
    artistEdit = new QLineEdit(editorBox);
    artistEdit->setText(QString::fromStdString(tag->artist().to8Bit(true)));

    commentLabel = new QLabel("Comment:", editorBox);
    commentEdit = new QLineEdit(editorBox);
    commentEdit->setText(QString::fromStdString(tag->comment().to8Bit(true)));

    saveButton = new QPushButton("Save tags", editorBox);
    QObject::connect(saveButton, SIGNAL(clicked()), this, SLOT(saveTags()));
    createLayout();

}

/*
A virtual method which saves (NOT THE FILE) the tags entered by the user
*/
void TagEditor::saveTags() {

    tag->setTitle(titleEdit->text().toStdString());
    tag->setTrack(trackEdit->text().toInt());
    tag->setAlbum(albumEdit->text().toStdString());
    tag->setYear(yearEdit->text().toInt());
    tag->setArtist(artistEdit->text().toStdString());
    tag->setComment(commentEdit->text().toStdString());

}

/*
A virtual method which adds all widgets to a layout
*/
void TagEditor::createLayout() {

    int i = layout->rowCount();
    layout->addWidget(titleLabel, i, 0);
    layout->addWidget(titleEdit, i, 1);
    i++;
    layout->addWidget(trackLabel, i, 0);
    layout->addWidget(trackEdit, i, 1);
    i++;
    layout->addWidget(albumLabel, i, 0);
    layout->addWidget(albumEdit, i, 1);
    i++;
    layout->addWidget(yearLabel, i, 0);
    layout->addWidget(yearEdit, i, 1);
    i++;
    layout->addWidget(artistLabel, i, 0);
    layout->addWidget(artistEdit, i, 1);
    i++;
    layout->addWidget(commentLabel, i, 0);
    layout->addWidget(commentEdit, i, 1);
    i++;
    layout->addWidget(saveButton, i, 3);
    editorBox->setLayout(layout);

}
