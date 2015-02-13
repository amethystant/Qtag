#include "id3v1editor.h"

Id3v1Editor::Id3v1Editor(TagLib::FileRef *file, QWidget *parent) :
    TagEditor(file, "ID3v1 tag", parent) {

    genreEdit = new Id3GenreSelection(editorBox);
    genreLabel = new QLabel("Genre:", parent);
    createLayout();

}

Id3v1Editor::~Id3v1Editor() {

}

void Id3v1Editor::createLayout() {

    TagEditor::createLayout();
    layout->removeWidget(saveButton);
    layout->addWidget(genreLabel, layout->columnCount()+1, 0);
    layout->addWidget(genreEdit, layout->columnCount(), 1);
    layout->addWidget(saveButton, layout->columnCount()+1, 0);

}

void Id3v1Editor::saveTags() {

    TagEditor::saveTags();
    tag->setGenre(genreEdit->currentText().toStdString());
    file->save();

}
