#include "multipletaggingdialog.h"
#include "main.h"
#include "audiofile.h"
#include <QPushButton>
#include <QFileDialog>
#include <QGridLayout>

MultipleTaggingDialog::MultipleTaggingDialog(QWidget *parent) :
    QDialog(parent) {

    setWindowTitle("Multiple tagging");

    filesLabel = new QLabel("Files:", this);
    filesEdit = new QLineEdit(this);
    filesEdit->setReadOnly(true);
    selectFilesButton  = new QPushButton("Select files", this);
    filesGroup = new QGroupBox("Files", this);

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
    xiphCommentCheck = new QCheckBox("Xiph Comment", this);
    xiphCommentCheck->setChecked(true);
    tagsGroup = new QGroupBox("Include:", this);

    titleCheck = new QCheckBox("Title:", this);
    titleCheck->setChecked(true);
    trackCheck = new QCheckBox("Track:", this);
    trackCheck->setChecked(true);
    albumCheck = new QCheckBox("Album:", this);
    albumCheck->setChecked(true);
    artistCheck = new QCheckBox("Artist:", this);
    artistCheck->setChecked(true);
    genreCheck = new QCheckBox("Genre:", this);
    genreCheck->setChecked(true);
    yearCheck = new QCheckBox("Year:", this);
    yearCheck->setChecked(true);
    commentCheck = new QCheckBox("Comment:", this);
    commentCheck->setChecked(true);
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

     QObject::connect(selectFilesButton, SIGNAL(clicked()), this, SLOT(openFiles()));
     QObject::connect(okButton, SIGNAL(clicked()), this, SLOT(startTagging()));
     QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));

     createLayout();

}

void MultipleTaggingDialog::createLayout() {

    QGridLayout* layout = new QGridLayout(this);
    int i = 0;

    QGridLayout* layout1 = new QGridLayout(this);
    layout1->addWidget(filesLabel, 0, 0);
    layout1->addWidget(filesEdit, 0, 1);
    layout1->addWidget(selectFilesButton, 1, 0);
    filesGroup->setLayout(layout1);

    QVBoxLayout* layout2 = new QVBoxLayout(this);
    layout2->addWidget(apeCheck);
    layout2->addWidget(asfCheck);
    layout2->addWidget(id3v1Check);
    layout2->addWidget(id3v2Check);
    layout2->addWidget(xiphCommentCheck);
    layout2->addWidget(infoTagCheck);
    tagsGroup->setLayout(layout2);

    QGridLayout* layout3 = new QGridLayout(this);
    layout3->addWidget(titleCheck, i, 0);
    layout3->addWidget(titleEdit, i, 1);
    i++;
    layout3->addWidget(trackCheck, i, 0);
    layout3->addWidget(trackEdit, i, 1);
    i++;
    layout3->addWidget(albumCheck, i, 0);
    layout3->addWidget(albumEdit, i, 1);
    i++;
    layout3->addWidget(artistCheck, i, 0);
    layout3->addWidget(artistEdit, i, 1);
    i++;
    layout3->addWidget(genreCheck, i, 0);
    layout3->addWidget(genreEdit, i, 1);
    i++;
    layout3->addWidget(yearCheck, i, 0);
    layout3->addWidget(yearEdit, i, 1);
    i++;
    layout3->addWidget(commentCheck, i, 0);
    layout3->addWidget(commentEdit, i, 1);
    editorGroup->setLayout(layout3);

    QHBoxLayout* layout4 = new QHBoxLayout(this);
    layout4->addWidget(cancelButton);
    layout4->addWidget(okButton);

    i = layout->rowCount();
    layout->addWidget(filesGroup, i, 0);
    i++;
    layout->addWidget(tagsGroup, i, 0);
    i++;
    layout->addWidget(editorGroup, i, 0);
    i++;
    layout->addLayout(layout4, i, 0);

}

void MultipleTaggingDialog::openFiles() {

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setOption(QFileDialog::DontUseNativeDialog);
#ifdef WIN32
    dialog.setDirectory("C:/");
#else
    dialog.setDirectory("/home");
#endif
    dialog.setNameFilter(
                tr(NAME_FILTER.c_str()));
    dialog.setViewMode(QFileDialog::Detail);
    dialog.show();
    if(dialog.exec()) {

        listOfFiles = dialog.selectedFiles();
        filesEdit->clear();
        filesEdit->insert(listOfFiles.join("; "));

    }

}

void MultipleTaggingDialog::saveTagsTo(QString nameOfTag, QString path) {

    AudioFile file(path, NULL);
    TagLib::Tag* tag = file.getTagByName(nameOfTag);
    if(tag == NULL)
        return;

    if(titleCheck->isChecked())
        tag->setTitle(titleEdit->text().toStdString());
    if(trackCheck->isChecked())
        tag->setTrack(trackEdit->text().toInt());
    if(albumCheck->isChecked())
        tag->setAlbum(albumEdit->text().toStdString());
    if(artistCheck->isChecked())
        tag->setArtist(artistEdit->text().toStdString());
    if(commentCheck->isChecked())
        tag->setComment(commentEdit->text().toStdString());
    if(genreCheck->isChecked())
        tag->setGenre(genreEdit->currentText().toStdString());
    if(yearCheck->isChecked())
        tag->setYear(yearEdit->text().toInt());

    file.save();

}

void MultipleTaggingDialog::startTagging() {

    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle(this->windowTitle());
    QLabel* label = new QLabel("Please wait...", dialog);
    QPushButton *button = new QPushButton("OK", dialog);
    button->setEnabled(false);
    QObject::connect(button, SIGNAL(clicked()), dialog, SLOT(close()));
    QObject::connect(button, SIGNAL(clicked()), this, SLOT(close()));
    QGridLayout* layout = new QGridLayout(dialog);
    layout->addWidget(label, 0, 0);
    layout->addWidget(button, 1, 1);
    dialog->setLayout(layout);
    dialog->show();



    label->clear();
    label->setText("Done.");
    dialog->update();
    button->setEnabled(true);

}
