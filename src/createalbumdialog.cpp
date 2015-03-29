#include "createalbumdialog.h"

#include <QFileDialog>
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
    id3v1Check->setChecked(true);
    id3v2Check = new QCheckBox("ID3v2 tags", this);
    id3v2Check->setChecked(true);
    infoTagCheck = new QCheckBox("RIFF Info tags", this);
    infoTagCheck->setChecked(true);
    xiphCommentCheck = new QCheckBox("Xiph Comments", this);
    xiphCommentCheck->setChecked(true);
    tagsGroup = new QGroupBox("Apply to", this);

    startTaggingButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Cancel", this);

    setWindowTitle("Create album from path");
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

    layout->addWidget(directoryGroup);
    layout->addWidget(tagFormatGroup);
    layout->addWidget(additionalChangesGroup);
    layout->addWidget(tagsGroup);
    layout->addLayout(layout7);
    setLayout(layout);

}

void CreateAlbumDialog::openDirectorySelection() {

    QFileDialog d(this);
    d.setFileMode(QFileDialog::DirectoryOnly);
    d.setOption(QFileDialog::DontUseNativeDialog);
#ifdef WIN32
    d.setDirectory("C:/");
#else
    d.setDirectory("/home");
#endif
    d.setViewMode(QFileDialog::Detail);
    d.show();
    if(d.exec()) {
        directoryEdit->setText(d.selectedFiles().at(0));
    }

}

void CreateAlbumDialog::showHint() {

    QDialog hint(this);
    hint.setWindowTitle("Tag format - hint");
    QLabel* l  = new QLabel(&hint);
    l->setText(
                "Tag formating - symbols: \n\n"
                "/ - directory separator (like usually) \n"
                "%a - artist \n"
                "%l - album \n"
                "%r - track number (can be both 01 or just 1\n"
                "%t - title\n"
                "\"string\" - a string that is common to all files, eg. -, ---, _, etc\n\n"
                "Example:\n"
                "%a/%l/%r\"---\"%t\n"
                "The filename extension must NOT be included in the format");
    QPushButton* b = new QPushButton("Close", &hint);
    QObject::connect(b, SIGNAL(clicked()), &hint, SLOT(close()));
    QVBoxLayout* lay = new QVBoxLayout(&hint);
    lay->addWidget(l);
    lay->addWidget(b);
    hint.setLayout(lay);
    hint.exec();

}

void CreateAlbumDialog::startTagging() {



}
