#include "id3v2editor.h"

Id3v2Editor::Id3v2Editor(TagLib::ID3v2::Tag *tag, QWidget *parent) :
    TagEditor(tag, "ID3v2 tag", parent) {

    id3v2Tag = tag;
    genreEdit = new Id3GenreSelection(this);
    int i = genreEdit->findText(QString::fromLocal8Bit(id3v2Tag->genre().toCString()));
    genreEdit->setCurrentIndex(i);
    genreLabel = new QLabel("Genre:", this);
    pictureLabel = new QLabel("Cover:", this);
    picturePath = new QString();
    picturePreview = new QLabel();
    picturePreview->setPixmap(QPixmap::fromImage(QImage(":images/nofile.png")));
    extractPictureFromTag();
    pictureSelection = new PictureSelectionButton(this, picturePath, picturePreview);
    extractPictureButton = new QPushButton("Save as a file...", this);
    removeCoverButton = new QPushButton("Remove cover", this);
    pictureFullSizeButton = new QPushButton("Show full size");
    QObject::connect(removeCoverButton, SIGNAL(clicked()), this, SLOT(removeCover()));
    QObject::connect(genreEdit, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTags()));
    QObject::connect(pictureSelection, SIGNAL(pictureChanged()), this, SLOT(updateTags()));
    QObject::connect(extractPictureButton, SIGNAL(clicked(bool)), this, SLOT(savePictureAsFile()));
    QObject::connect(pictureFullSizeButton, SIGNAL(clicked()), this, SLOT(showPictureFullSize()));
    createLayout();

}

/*
Overrides TagEditor::createLayout() and adds some ID3v2 specific
widgets to the layout
*/
void Id3v2Editor::createLayout() {

    int i = layout->rowCount();
    layout->addWidget(pictureLabel, i, 0);
    layout->addWidget(picturePreview, i, 1);
    i++;

    QHBoxLayout* l = new QHBoxLayout(this);
    l->addWidget(pictureSelection);
    l->addWidget(removeCoverButton);
    layout->addLayout(l, i, 0, 2, 0);
    i+=2;
    layout->addWidget(extractPictureButton, i, 0);
    layout->addWidget(pictureFullSizeButton, i, 1);

    TagEditor::createLayout();
    i = layout->rowCount();
    layout->addWidget(genreLabel, i, 0);
    layout->addWidget(genreEdit, i, 1);

}

/*
Overrides TagEditor::saveTags() and updates some ID3v2 specific tags
*/
void Id3v2Editor::updateTags() {

    TagEditor::updateTags();
    id3v2Tag->setGenre(genreEdit->currentText().toStdString());

    if(!picturePath->isEmpty()) {

        TagLib::ID3v2::AttachedPictureFrame* frame = new TagLib::ID3v2::AttachedPictureFrame();
        if(picturePath->endsWith(".jpeg", Qt::CaseInsensitive) || picturePath->endsWith(".jpg"), Qt::CaseInsensitive)
            frame->setMimeType("image/jpeg");
        else if(picturePath->endsWith(".png"), Qt::CaseInsensitive)
            frame->setMimeType("image/png");
        id3v2Tag->removeFrames("APIC");
        PictureFile pictureFile(picturePath->toStdString().c_str());
        frame->setPicture(pictureFile.getData());
        id3v2Tag->addFrame(frame);

    }

}

/*This method extracts the cover from the tag and shows it to the user*/
void Id3v2Editor::extractPictureFromTag() {

    QImage image;
    TagLib::ID3v2::FrameList frameList = id3v2Tag->frameList("APIC");
    if(frameList.isEmpty()) {
        picturePreview->setPixmap(QPixmap::fromImage(QImage(":images/nofile.png")));
        return;
     }
    TagLib::ID3v2::AttachedPictureFrame *pictureFrame =
        static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frameList.front());
    image.loadFromData((const uchar *) pictureFrame->picture().data(), pictureFrame->picture().size());
    image = image.scaled(100, 100);
    picturePreview->clear();
    picturePreview->setPixmap(QPixmap::fromImage(image));
    picturePreview->update();

}

void Id3v2Editor::removeCover() {

    picturePath->clear();
    picturePreview->setPixmap(QPixmap::fromImage(QImage(":images/nofile.png")));
    id3v2Tag->removeFrames("APIC");

}

void Id3v2Editor::savePictureAsFile() {

    QImage image;
    TagLib::ID3v2::FrameList frameList = id3v2Tag->frameList("APIC");
    if(frameList.isEmpty()) {
        QMessageBox::warning(this, "Warning", "There is no picture to save.");
        return;
    }
    TagLib::ID3v2::AttachedPictureFrame *pictureFrame =
            static_cast<TagLib::ID3v2::AttachedPictureFrame*>(frameList.front());
    image.loadFromData((const uchar*) pictureFrame->picture().data(), pictureFrame->picture().size());
    QString fileName = QFileDialog::getSaveFileName(this, "Save cover", 0, "PNG Images (*.png)");
    image.save(fileName);

}

void Id3v2Editor::showPictureFullSize() {

    QImage image;
    TagLib::ID3v2::FrameList frameList = id3v2Tag->frameList("APIC");
    if(frameList.isEmpty()) {
        QMessageBox::warning(this, "Error", "There is no picture to show.");
        return;
    }
    TagLib::ID3v2::AttachedPictureFrame *pictureFrame =
            static_cast<TagLib::ID3v2::AttachedPictureFrame*>(frameList.front());
    image.loadFromData((const uchar*) pictureFrame->picture().data(), pictureFrame->picture().size());

    QScrollArea* window = new QScrollArea;
    QLabel* preview = new QLabel(window);
    preview->setPixmap(QPixmap::fromImage(image));
    window->setWidget(preview);
    window->show();

}
