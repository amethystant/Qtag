#include "multipletaggingdialog.h"
#include <QPushButton>

MultipleTaggingDialog::MultipleTaggingDialog(QWidget *parent) :
    QDialog(parent) {

    filesLabel = new QLabel("Files:", this);
    filesEdit = new QLineEdit(this);
    filesEdit->setReadOnly(true);
    selectFilesButton  = new QPushButton("Select files:", this);
    filesGroup = new QGroupBox("Files", this);

    apeCheck = new QCheckBox("APE tags", this);
    asfCheck = new QCheckBox("ASF tags", this);
    id3v1Check = new QCheckBox("ID3v1 tags", this);
    id3v2Check = new QCheckBox("ID3v2 tags", this);
    infoTagCheck = new QCheckBox("RIFF Info tags", this);
    xiphCommentCheck = new QCheckBox("Xiph Comment", this);
    tagsGroup = new QGroupBox("Include:", this);

    titleCheck = new QCheckBox("Title:", this);
    trackCheck = new QCheckBox("Track:", this);
    albumCheck = new QCheckBox("Album:", this);
    artistCheck = new QCheckBox("Artist:", this);
    genreCheck = new QCheckBox("Genre:", this);
    yearCheck = new QCheckBox("Year:", this);
    commentCheck = new QCheckBox("Comment:", this);
    titleEdit = new QLineEdit(this);
    trackEdit = new QLineEdit(this);
    albumEdit = new QLineEdit(this);
    artistEdit = new QLineEdit(this);
    genreEdit = new Id3GenreSelection(this);
    yearEdit = new QLineEdit(this);
    yearEdit->setValidator(new QIntValidator(0, 10000, yearEdit));
    commentEdit = new QLineEdit(this);
    editorGroup = new QGroupBox("Tags", this);

     okButton = new QPushButton("OK", this);
     cancelButton = new QPushButton("Cancel", this);

     QObject::connect(titleCheck, SIGNAL(clicked(bool)), titleEdit, SLOT(setEnabled(bool)));
     QObject::connect(trackCheck, SIGNAL(clicked(bool)), trackEdit, SLOT(setEnabled(bool)));
     QObject::connect(albumCheck, SIGNAL(clicked(bool)), albumEdit, SLOT(setEnabled(bool)));
     QObject::connect(artistCheck, SIGNAL(clicked(bool)), artistEdit, SLOT(setEnabled(bool)));
     QObject::connect(genreCheck, SIGNAL(clicked(bool)), genreEdit, SLOT(setEnabled(bool)));
     QObject::connect(yearCheck, SIGNAL(clicked(bool)), yearEdit, SLOT(setEnabled(bool)));
     QObject::connect(commentCheck, SIGNAL(clicked(bool)), commentEdit, SLOT(setEnabled(bool)));

     QObject::connect(okButton, SIGNAL(clicked()), this, SLOT(startTagging()));
     QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));

     createLayout();

}

void MultipleTaggingDialog::createLayout() {

}

void MultipleTaggingDialog::startTagging() {

}
