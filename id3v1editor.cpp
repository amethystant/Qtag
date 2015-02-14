#include "id3v1editor.h"

Id3v1Editor::Id3v1Editor(TagLib::FileRef *file, QWidget *parent) :
    TagEditor(file, "ID3v1 tag", parent) {

    genreEdit = new Id3GenreSelection(editorBox);
    genreLabel = new QLabel("Genre:", parent);
    createLayout();

}

Id3v1Editor::~Id3v1Editor() {

}

/*
Overrides TagEditor::createLayout() and adds some ID3v1 specific
widgets to the layout
*/
void Id3v1Editor::createLayout() {

    TagEditor::createLayout();
    layout->removeWidget(saveButton);
    layout->addWidget(genreLabel, layout->columnCount()+1, 0);
    layout->addWidget(genreEdit, layout->columnCount(), 1);
    layout->addWidget(saveButton, layout->columnCount()+1, 0);

}

/*
Overrides TagEditor::saveTags() and saves some ID3v1 specific tags
*/
void Id3v1Editor::saveTags() {

    TagEditor::saveTags();
    tag->setGenre(genreEdit->currentText().toStdString());
    file->save();

}
