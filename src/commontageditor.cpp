#include "commontageditor.h"

CommonTagEditor::CommonTagEditor(TagLib::Tag *tag, QString nameOfTag, QWidget *parent) :
    TagEditor(tag, nameOfTag, parent) {

    genreEdit = new QLineEdit(this);
    genreEdit->setText(QString::fromLocal8Bit(tag->genre().toCString(true)));
    genreLabel = new QLabel("Genre:", this);

    createLayout();
    QObject::connect(genreEdit, SIGNAL(textEdited(QString)), this, SLOT(updateTags()));

}

/*
 *Overrides TagEditor::saveTags() and updates the genre tag
*/
void CommonTagEditor::updateTags() {

    TagEditor::updateTags();
    tag->setGenre(genreEdit->text().toStdString());

}

/*
 *Overrides TagEditor::createLayout() and adds the genre editor
 *to the layout
*/
void CommonTagEditor::createLayout() {

    TagEditor::createLayout();
    int i = layout->rowCount();
    layout->addWidget(genreLabel, i, 0);
    layout->addWidget(genreEdit, i, 1);

}
