#include "tageditor.h"

TagEditor::TagEditor(TagLib::Tag* tag, QString nameOfTag, QWidget *parent) {

    this->tag = tag;
    editorBox = new QGroupBox(parent);
    nameLabel = new QLabel(nameOfTag, editorBox);

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

}

TagEditor::~TagEditor() {

}

void TagEditor::saveTags() {

}
