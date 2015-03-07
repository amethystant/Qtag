#include "apetageditor.h"

ApeTagEditor::ApeTagEditor(TagLib::APE::Tag *tag, QWidget *parent) :
    CommonTagEditor(tag, "APE Tag", parent) {
    apeTag = tag;
}

void ApeTagEditor::updateTags() {
    CommonTagEditor::updateTags();
}

void ApeTagEditor::createLayout() {
    CommonTagEditor::createLayout();
}
