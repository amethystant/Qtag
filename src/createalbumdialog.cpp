#include "createalbumdialog.h"
#include <QGridLayout>

CreateAlbumDialog::CreateAlbumDialog(QWidget *parent) :
    QDialog(parent) {

    directoryLabel = new QLabel("Root directory:", this);
    directoryEdit = new QLineEdit(this);
    directoryEdit->setReadOnly(true);
    directorySelectionButton = new QPushButton("Browse...", this);
    directoryGroup = new QGroupBox("Directory", this);

    tagFormatLabel = new QLabel("Tag format:", this);
    tagFormatEdit = new QLineEdit(this);
    hintButton = new QPushButton("Show hint", this);
    tagFormatGroup = new QGroupBox("Tag format", this);

    makeCapitalLettersCheck = new QCheckBox("make capital letters", this);
    replaceStringLabel = new QLabel("Replace:", this);
    replaceStringEdit = new QLineEdit(this);
    replaceByLabel = new QLabel("Replace by:", this);
    replaceByEdit = new QLineEdit(this);
    additionalChangesGroup = new QGroupBox("Additional changes", this);

    apeCheck = new QCheckBox("APE tags", this);
    apeCheck->setChecked(true);
    asfCheck = new QCheckBox("ASF tags", this);
    asfCheck->setChecked(true);
    id3v1Check = new QCheckBox("ID3v1 tags", this);
    id3v2Check->setChecked(true);
    id3v2Check = new QCheckBox("ID3v2 tags", this);
    id3v2Check->setChecked(true);
    infoTagCheck = new QCheckBox("RIFF Info tags", this);
    infoTagCheck->setChecked(true);
    xiphCommentCheck = new QCheckBox("Xiph Comments", this);
    xiphCommentCheck->setChecked(true);
    tagsGroup = new QGroupBox("Apply to", this);

    startTaggingButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Cancel", this);

    createLayout();

    QObject::connect(directorySelectionButton, SIGNAL(clicked()), this, SLOT(openDirectorySelection()));
    QObject::connect(hintButton,SIGNAL(clicked()), this, SLOT(showHint()));
    QObject::connect(startTaggingButton, SIGNAL(clicked()), this, SLOT(startTagging()));
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));

}

void CreateAlbumDialog::createLayout() {

    QVBoxLayout* layout = new QVBoxLayout(this);

    QGridLayout* layout1 = new QGridLayout(this);
    layout1->addWidget(directoryLabel, 0, 0);
    layout1->addWidget(directoryEdit, 0, 1);
    layout1->addWidget(directorySelectionButton, 1, 0);
    directoryGroup->setLayout(layout1);

    QGridLayout* layout2 = new QGridLayout(this);
    layout2->addWidget(tagFormatLabel, 0, 0);
    layout2->addWidget(tagFormatEdit, 0, 1);
    layout2->addWidget(hintButton, 1, 0);
    tagFormatGroup->setLayout(layout2);

    QHBoxLayout* layout3 = new QHBoxLayout(this);
    layout3->addWidget(replaceStringLabel);
    layout3->addWidget(replaceStringEdit);
    QHBoxLayout* layout4 = new QHBoxLayout(this);
    layout4->addWidget(replaceByLabel);
    layout4->addWidget(replaceByEdit);
    QVBoxLayout* layout5 = new QVBoxLayout(this);
    layout5->addWidget(makeCapitalLettersCheck);
    layout5->addLayout(layout3);
    layout5->addLayout(layout4);
    additionalChangesGroup->setLayout(layout5);

    QVBoxLayout* layout6 = new QVBoxLayout(this);
    layout6->addWidget(apeCheck);
    layout6->addWidget(asfCheck);
    layout6->addWidget(id3v1Check);
    layout6->addWidget(id3v2Check);
    layout6->addWidget(infoTagCheck);
    layout6->addWidget(xiphCommentCheck);
    tagsGroup->setLayout(layout6);

    QHBoxLayout* layout7 = new QHBoxLayout(this);
    layout7->addWidget(startTaggingButton);
    layout7->addWidget(cancelButton);

    layout->addLayout(layout1);
    layout->addLayout(layout2);
    layout->addLayout(layout3);
    layout->addLayout(layout4);
    layout->addLayout(layout5);
    layout->addLayout(layout6);
    layout->addLayout(layout7);
    setLayout(layout);

}

void CreateAlbumDialog::openDirectorySelection() {



}

void CreateAlbumDialog::showHint() {



}

void CreateAlbumDialog::startTagging() {



}
