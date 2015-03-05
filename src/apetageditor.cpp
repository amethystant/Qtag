#include "apetageditor.h"

ApeTagEditor::ApeTagEditor(TagLib::APE::Tag *tag, QWidget *parent) : TagEditor(tag, "APE Tag", parent) {

    apeTag = tag;
    genreEdit = new QLineEdit(this);
    genreEdit->setText(QString::fromLocal8Bit(apeTag->genre().toCString(true)));
    genreLabel = new QLabel("Genre:", this);

    createLayout();
    QObject::connect(genreEdit, SIGNAL(textEdited(QString)), this, SLOT(updateTags()));

}


/*
 *Overrides TagEditor::saveTags() and updates some APE specific tags
*/
void ApeTagEditor::updateTags() {

    TagEditor::updateTags();
    tag->setGenre(genreEdit->text().toStdString());

}

/*
 *Overrides TagEditor::createLayout() and adds some APE specific
 *widgets to the layout
*/
void ApeTagEditor::createLayout() {

    TagEditor::createLayout();
    int i = layout->rowCount();
    layout->addWidget(genreLabel, i, 0);
    layout->addWidget(genreEdit, i, 1);

}
