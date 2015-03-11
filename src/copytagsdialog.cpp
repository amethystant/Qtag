#include "copytagsdialog.h"
#include "main.h"
#include <QPushButton>
#include <QGridLayout>

CopyTagsDialog::CopyTagsDialog(QWidget *parent, QList<AudioFile*> *listOfFiles) : QDialog(parent) {

    setWindowTitle("Copy Tags");
    this->listOfFiles = listOfFiles;

    targetTagLabel = new QLabel("Target tag:", this);
    targetFileLabel = new QLabel("Target file:", this);
    sourceFileLabel = new QLabel("Source file:", this);
    sourceTagLabel = new QLabel("Source Tag:", this);

    sourceFileSelection = new QComboBox(this);
    sourceTagSelection = new QComboBox(this);
    targetFileSelection = new QComboBox(this);
    targetTagSelection = new QComboBox(this);

    okButton = new QPushButton("OK", this);

    sourceTagSelection->setEnabled(false);
    targetTagSelection->setEnabled(false);
    okButton->setEnabled(false);

    QObject::connect(sourceFileSelection, SIGNAL(currentIndexChanged(int)), this, SLOT(updateComboBoxes()));
    QObject::connect(targetFileSelection, SIGNAL(currentIndexChanged(int)), this, SLOT(updateComboBoxes()));
    QObject::connect(okButton, SIGNAL(clicked()), this, SLOT(startCopying()));
    initComboBoxes();
    createLayout();

}

void CopyTagsDialog::initComboBoxes() {

    int i;
    for(i = 0; i < listOfFiles->length(); i++) {
        QString path = listOfFiles->at(i)->getPath();
        sourceFileSelection->addItem(path);
        targetFileSelection->addItem(path);
    }

}

void CopyTagsDialog::createLayout() {

    QGridLayout* layout = new QGridLayout(this);
    int i = 0;
    layout->addWidget(sourceFileLabel, i, 0);
    layout->addWidget(sourceFileSelection, i, 1);
    i++;
    layout->addWidget(sourceTagLabel, i, 0);
    layout->addWidget(sourceTagSelection, i, 1);
    i++;
    layout->addWidget(targetFileLabel, i, 0);
    layout->addWidget(targetFileSelection, i, 1);
    i++;
    layout->addWidget(targetTagLabel, i, 0);
    layout->addWidget(targetTagSelection, i, 1);
    i++;
    layout->addWidget(okButton, i, 3);

}

/*
 * This method is called when the user clicks on a QComboBox and changes
 * the source file or the target file. Determines which tags
 * exist in the selected files and the updates the other QComboBoxes.
*/
void CopyTagsDialog::updateComboBoxes() {

    QString selectedFile = sourceFileSelection->currentText();
    AudioFile* file;
    int i;
    for(i = 0; i < listOfFiles->length(); i++) {
        AudioFile* f = listOfFiles->at(i);
        if(f->getPath().compare(selectedFile) == 0) {
            file = f;
            i = listOfFiles->length();
        }
    }

    sourceTagSelection->clear();

    if(file->hasApeTag())
        sourceTagSelection->addItem(QString::fromStdString(NamesOfTags::APE));
    if(file->hasAsfTag())
        sourceTagSelection->addItem(QString::fromStdString(NamesOfTags::ASF));
    if(file->hasId3v1())
        sourceTagSelection->addItem(QString::fromStdString(NamesOfTags::ID3V1));
    if(file->hasId3v2())
        sourceTagSelection->addItem(QString::fromStdString(NamesOfTags::ID3V2));
    if(file->hasInfoTag())
        sourceTagSelection->addItem(QString::fromStdString(NamesOfTags::INFO));
    if(file->hasXiphComment())
        sourceTagSelection->addItem(QString::fromStdString(NamesOfTags::XIPH));

    sourceTagSelection->setEnabled(true);

    selectedFile = targetFileSelection->currentText();
    for(i = 0; i < listOfFiles->length(); i++) {
        AudioFile* f = listOfFiles->at(i);
        if(f->getPath().compare(selectedFile) == 0) {
            file = f;
            i = listOfFiles->length();
        }
    }

    targetTagSelection->clear();

    if(file->hasApeTag())
        targetTagSelection->addItem(QString::fromStdString(NamesOfTags::APE));
    if(file->hasAsfTag())
        targetTagSelection->addItem(QString::fromStdString(NamesOfTags::ASF));
    if(file->hasId3v1())
        targetTagSelection->addItem(QString::fromStdString(NamesOfTags::ID3V1));
    if(file->hasId3v2())
        targetTagSelection->addItem(QString::fromStdString(NamesOfTags::ID3V2));
    if(file->hasInfoTag())
        targetTagSelection->addItem(QString::fromStdString(NamesOfTags::INFO));
    if(file->hasXiphComment())
        targetTagSelection->addItem(QString::fromStdString(NamesOfTags::XIPH));

    targetTagSelection->setEnabled(true);
    if(targetTagSelection->isEnabled() && sourceTagSelection->isEnabled())
        okButton->setEnabled(true);
    else
        okButton->setDisabled(true);

}

void CopyTagsDialog::copyTags(TagLib::Tag* sourceTag, TagLib::Tag* targetTag) {

    targetTag->setTitle(sourceTag->title());
    targetTag->setTrack(sourceTag->track());
    targetTag->setGenre(sourceTag->genre());
    targetTag->setComment(sourceTag->comment());
    targetTag->setAlbum(sourceTag->album());
    targetTag->setArtist(sourceTag->artist());
    targetTag->setYear(sourceTag->year());

}

void CopyTagsDialog::startCopying() {

    QDialog* dialog = new QDialog(this, 0);
    dialog->setWindowTitle("Copying...");
    QLabel* label = new QLabel("Please wait...", dialog);
    dialog->setBaseSize(300, 200);
    QGridLayout* layout = new QGridLayout(dialog);
    layout->addWidget(label);
    dialog->show();

    AudioFile* sourceFile;
    AudioFile* targetFile;
    int i;
    for(i = 0; i < listOfFiles->length(); i++) {
        AudioFile* f = listOfFiles->at(i);
        if(f->getPath().compare(sourceFileSelection->currentText()) == 0) {
            sourceFile = f;
        }
        if(f->getPath().compare(targetFileSelection->currentText()) == 0) {
            targetFile = f;
        }
    }

    copyTags(sourceFile->getTagByName(sourceTagSelection->currentText()),
             targetFile->getTagByName(targetTagSelection->currentText()));

    layout->removeWidget(label);
    label->clear();
    label->setText("Done");
    QPushButton* button = new QPushButton("OK", dialog);
    layout->addWidget(button,1, 1);
    QObject::connect(button, SIGNAL(clicked()), dialog, SLOT(close()));
    QObject::connect(button, SIGNAL(clicked()), this, SLOT(close()));
    dialog->update();

}
