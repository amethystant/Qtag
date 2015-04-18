#include "createalbumdialog.h"
#include "main.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QGridLayout>
#include <QDir>
#include <QDirIterator>
#include <QRegExp>

CreateAlbumDialog::CreateAlbumDialog(QWidget *parent, FileList* list) :
    QDialog(parent) {

    fileList = list;

    directoryLabel = new QLabel("Root directory:", this);
    directoryEdit = new QLineEdit(this);
    directoryEdit->setReadOnly(true);
    directorySelectionButton = new QPushButton("Browse...", this);
    directoryGroup = new QGroupBox("Directory", this);

    tagFormatLabel = new QLabel("Tag format:", this);
    tagFormatEdit = new QLineEdit(this);
    hintButton = new QPushButton("Show hint", this);
    tagFormatGroup = new QGroupBox("Tag format", this);

    makeCapitalLettersCheck = new QCheckBox("capitalize letters", this);
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

/*
*Called when the user clicks on the button "show hint". 
*Displays a dialog with a review of the tag formating symbols
*/
void CreateAlbumDialog::showHint() {

    QDialog hint(this);
    hint.setWindowTitle("Tag format - hint");
    QLabel* l  = new QLabel(&hint);
    l->setText(
                "<b>Tag formating - symbols:</b> <br>"
                "/ - directory separator (like usually) <br>"
                "%a - artist <br>"
                "%l - album <br>"
                "%r - track number (can be both 01 or just 1)<br>"
                "%t - title<br>"
                "* - any string<br>"
                "? - any character<br>"
                "static strings (such as ---, _, -, etc) don't need to be in quotation marks<br><br>"
                "<b>Example:</b><br>"
                "<font color=green>%a/%l/%r---%t</font>         correct<br><br>"
                "<font color=red>%a/%l/%r---%t.ogg</font>       incorrect*<br>"
                "<font color=red>%a%l%t</font>                  incorrect**<br>"
                "<font color=red>%a?%l/*%r%t</font>             incorrect**<br><br>"
                "*The filename extension must NOT be included in the format<br>"
                "**All symbols and wildcards must be separated by a static string");
    QPushButton* b = new QPushButton("Close", &hint);
    QObject::connect(b, SIGNAL(clicked()), &hint, SLOT(close()));
    QVBoxLayout* lay = new QVBoxLayout(&hint);
    lay->addWidget(l);
    lay->addWidget(b);
    hint.setLayout(lay);
    hint.exec();

}

/*
* Called if a wrong tag format is recognized.
* Displays an error message.
*/
void CreateAlbumDialog::tagFormatError() {

    QMessageBox* message = new QMessageBox(this);
    message->setWindowTitle("Error");
    message->setText("Error - invalid tag format.");
    message->setStandardButtons(QMessageBox::Ok);
    message->exec();

}

void CreateAlbumDialog::saveTagsTo(AudioFile* f, std::string nameOfTag,
                                   QString title, QString track, QString album, QString artist) {

    TagLib::Tag* t = f->getTagByName(QString::fromStdString(nameOfTag));
    if(t == NULL) {
        return;
    }

    if(!title.isEmpty()) {
        t->setTitle(title.toStdString());
    }
    if(!track.isEmpty()) {
        if(track.startsWith('0'))
            track.remove(0, 1);
        t->setTrack(track.toInt());
    }
    if(!album.isEmpty()) {
        t->setAlbum(album.toStdString());
    }
    if(!artist.isEmpty()) {
        t->setArtist(artist.toStdString());
    }

    f->save();

}

void CreateAlbumDialog::startTagging() {

    QMessageBox* message = new QMessageBox(this);
    message->setWindowTitle("Please wait");
    message->setText("Please wait, this may take a few seconds...");
    message->setStandardButtons(QMessageBox::NoButton);
    message->show();

    if(directoryEdit->text().isEmpty()) {
        QMessageBox* msg = new QMessageBox(this);
        msg->setText("Invalid path to the root directory.");
        msg->setStandardButtons(QMessageBox::Ok);
        msg->exec();
        message->done(1);
        return;
    }

    QStringList nameFilters;
    QString filter = tagFormatEdit->text();

    if(filter.count('%') == 0) {
        tagFormatError();
        message->done(1);
        return;
    }

    while(filter.indexOf('*') != -1 && filter.length() != filter.indexOf('*')+1) {
        int i = filter.indexOf('*');
        if(filter.at(i+1) == '%' || filter.at(i+1) == '?'|| filter.at(i+1) == '*') {
            message->done(1);
            tagFormatError();
            return;
        }
    }

    while(filter.indexOf('?') != -1 && filter.length() != filter.indexOf('?')+1) {
        int i = filter.indexOf('?');
        if(filter.at(i+1) == '*' || filter.at(i+1) == '%' || filter.at(i+1) == '*') {
            message->done(1);
            tagFormatError();
            return;
        }
    }

    while(filter.indexOf('%') != -1) {
        int i = filter.indexOf('%');
        if(filter.length() - (i+1) == 1) {
            filter.replace(i, 2, '*');
        } else if(filter.endsWith('%') ||
              ( filter.at(i+1) != 'a' &&
                filter.at(i+1) != 'l' &&
                filter.at(i+1) != 'r' &&
                filter.at(i+1) != 't'    ) ||
                filter.at(i+2) == '*' ||
                filter.at(i+2) == '?' ||
                filter.at(i+2) == '%') {

            message->done(1);
            tagFormatError();
            return;

        } else {
            filter.replace(i, 2, "*");
        }
    }

    QString nameFilter = filter;
    int i = nameFilter.lastIndexOf('/');
    nameFilter.remove(0, i+1);

    nameFilters.append(nameFilter + ".mp3");
    nameFilters.append(nameFilter + ".asf");
    nameFilters.append(nameFilter + ".ogg");
    nameFilters.append(nameFilter + ".wma");
    nameFilters.append(nameFilter + ".flac");
    nameFilters.append(nameFilter + ".wv");
    nameFilters.append(nameFilter + ".wav");
    nameFilters.append(nameFilter + ".wave");

    QDirIterator dirIterator(directoryEdit->text(), nameFilters, QDir::Files,
                               QDirIterator::Subdirectories);

    QStringList* files = new QStringList();
    while(dirIterator.hasNext()) {
        files->append(dirIterator.next());
    }

    for(i = 0; i < files->length();) {
        QString s = files->at(i);
        s.remove(directoryEdit->text() + "/");
        if(s.count('/') != filter.count('/')) {
            files->removeAt(i);
        } else {
            i++;
        }
    }

    for(i = 0; i < files->length();) {

        QRegExp r(filter + ".*", Qt::CaseSensitive, QRegExp::Wildcard);
        if(!r.exactMatch(files->at(i))) {
            files->removeAt(i);
        } else {
            i++;
        }

    }

    if(files->isEmpty()) {
        QMessageBox* msg = new QMessageBox(this);
        msg->setWindowTitle("Error");
        msg->setText("No file matches the tag format.");
        msg->setStandardButtons(QMessageBox::Ok);
        msg->exec();
        message->done(1);
        return;
    }

    for(i = 0; i < files->length(); i++) {

        QString path = files->at(i);
        AudioFile* file = NULL;
        for(int i = 0; i < fileList->length(); i++) {
            AudioFile* f = fileList->at(i);
            if(f->getPath() == path) {
                file = f;
                i = fileList->length();
            }
        }
        if(file == NULL) {
            for(int i = 0; i < fileList->closed_length(); i++) {
                AudioFile* f = fileList->closed_at(i);
                if(f->getPath() == path) {
                    file = f;
                    i = fileList->closed_length();
                }
            }
        }
        if(file == NULL) {
            file = new AudioFile(path, this);
            fileList->addFileToList(path);
            fileList->closeFile(path);
        }

        QString currentFile = files->at(i);
        currentFile.remove(0, directoryEdit->text().length() + 1);
        currentFile.remove(currentFile.lastIndexOf('.'),
                           currentFile.length() - currentFile.lastIndexOf('.'));
        QString format = tagFormatEdit->text();
        QString title,
                track,
                album,
                artist;
        int loop = format.count('%') + format.count('*') + format.count('?');
        for(int i1 = 0; i1 < loop; i1++) {

            int index = format.indexOf('%');
            int index1 = format.indexOf('*');
            int index2 = format.indexOf('?');
            if((index < index1 || index1 == -1)&&
                    (index < index2 || index2 == -1) && index != -1) {

                QString s = format.section('%', 1, 1);
                QChar symbol  = s.at(0);
                s.remove(0, 1);
                int in = currentFile.indexOf(s);
                QString extractedString = currentFile.mid(index, in-index);
                format.replace(format.indexOf('%'), 2, extractedString);
                if(symbol == 'a') {
                    artist = extractedString;
                } else if(symbol == 'l') {
                    album = extractedString;
                } else if(symbol == 'r') {
                    track = extractedString;
                } else if(symbol == 't') {
                    title = extractedString;
                }

            } else if((index1 < index || index == -1) &&
                      (index1 < index2 || index2 == -1) && index1 != -1) {

                QString s = format.section('*', 1, 1);
                int in = currentFile.indexOf(s);
                QString extractedString = currentFile.mid(index1, in-index1);
                format.replace(format.indexOf('*'), 1, extractedString);


            } else if((index2 < index || index == -1) &&
                      (index2 < index1 || index1 == -1) && index2 != -1) {


                QString extractedChar = currentFile.mid(index1, 1);
                format.replace(format.indexOf('?'), 1, extractedChar);

            }

        }

        if(!replaceStringEdit->text().isEmpty()) {
            if(!title.isEmpty()) {
                title.replace(replaceStringEdit->text(), replaceByEdit->text());
            }
            if(!album.isEmpty()) {
                album.replace(replaceStringEdit->text(), replaceByEdit->text());
            }
            if(!artist.isEmpty()) {
                artist.replace(replaceStringEdit->text(), replaceByEdit->text());
            }
        }

        if(makeCapitalLettersCheck->isChecked()) {
            if(!artist.isEmpty()) {
                artist = capitalized(artist);
            }
            if(!album.isEmpty()) {
                album = capitalized(album);
            }
            if(!title.isEmpty()) {
                title = capitalized(title);
            }
        }

        if(apeCheck->isChecked())
            saveTagsTo(file, NamesOfTags::APE, title, track, album, artist);
        if(asfCheck->isChecked())
            saveTagsTo(file, NamesOfTags::ASF, title, track, album, artist);
        if(xiphCommentCheck->isChecked())
            saveTagsTo(file, NamesOfTags::XIPH, title, track, album, artist);
        if(id3v1Check->isChecked())
            saveTagsTo(file, NamesOfTags::ID3V1, title, track, album, artist);
        if(id3v2Check->isChecked())
            saveTagsTo(file, NamesOfTags::ID3V2, title, track, album, artist);
        if(infoTagCheck->isChecked())
            saveTagsTo(file, NamesOfTags::INFO, title, track, album, artist);

    }

    message->setText("Done.");
    message->setStandardButtons(QMessageBox::Ok);
    message->update();
    close();

}
