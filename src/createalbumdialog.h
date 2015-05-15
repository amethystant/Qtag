/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 *
 * (C) 2015 by Karel Patlejch
 *
 * Used libraries:
 *    TagLib - https://github.com/taglib
 *    Qt - http://qt.io
 *
*/

#ifndef CREATEALBUMDIALOG_H
#define CREATEALBUMDIALOG_H

#include <QCheckBox>
#include <QDialog>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "audiofile.h"
#include "filelist.h"

class CreateAlbumDialog : public QDialog {

    Q_OBJECT

public:
    CreateAlbumDialog(QWidget* parent, FileList *list);

private:
    FileList* fileList;

    QLabel* directoryLabel;
    QLineEdit* directoryEdit;
    QPushButton* directorySelectionButton;
    QGroupBox* directoryGroup;

    QLabel* tagFormatLabel;
    QLineEdit* tagFormatEdit;
    QPushButton* hintButton;
    QGroupBox* tagFormatGroup;

    QCheckBox* makeCapitalLettersCheck;
    QLabel* replaceStringLabel;
    QLineEdit* replaceStringEdit;
    QLabel* replaceByLabel;
    QLineEdit* replaceByEdit;
    QGroupBox* additionalChangesGroup;

    QCheckBox* apeCheck;
    QCheckBox* asfCheck;
    QCheckBox* id3v1Check;
    QCheckBox* id3v2Check;
    QCheckBox* infoTagCheck;
    QCheckBox* xiphCommentCheck;
    QGroupBox* tagsGroup;

    QPushButton* startTaggingButton;
    QPushButton* cancelButton;

    void createLayout();
    void tagFormatError();
    void saveTagsTo(AudioFile* f, std::string nameOfTag,
                    QString title, QString track, QString album, QString artist);

private slots:
    void openDirectorySelection();
    void showHint();
    void startTagging();

};

#endif // CREATEALBUMDIALOG_H
