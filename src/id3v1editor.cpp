#include "id3v1editor.h"

Id3v1Editor::Id3v1Editor(TagLib::ID3v1::Tag *tag, QWidget *parent) :
    TagEditor(tag, "ID3v1 tag", parent) {

    id3v1Tag = tag;
    genreEdit = new Id3GenreSelection(this);
    int i = genreEdit->findText(QString::fromLocal8Bit(id3v1Tag->genre().toCString()));
    genreEdit->setCurrentIndex(i);
    genreLabel = new QLabel("Genre:", this);
    QObject::connect(genreEdit, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTags()));
    createLayout();

}

/*
 *Overrides TagEditor::createLayout() and adds some ID3v1 specific
 *widgets to the layout
*/
void Id3v1Editor::createLayout() {

    TagEditor::createLayout();
    int i = layout->rowCount();
    layout->addWidget(genreLabel, i, 0);
    layout->addWidget(genreEdit, i, 1);

}

/*
 *Overrides TagEditor::saveTags() and updates some ID3v1 specific tags
*/
void Id3v1Editor::updateTags() {

    TagEditor::updateTags();
    id3v1Tag->setGenre(genreEdit->currentText().toStdString());

}
