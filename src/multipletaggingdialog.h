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

#ifndef MULTIPLETAGGINGDIALOG_H
#define MULTIPLETAGGINGDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QCheckBox>
#include <audiofile.h>
#include "id3genreselection.h"
#include "filelist.h"

class MultipleTaggingDialog : public QDialog {

    Q_OBJECT

public:
    MultipleTaggingDialog(QWidget* parent, FileList *list);

private:
    QLabel* filesLabel;
    QLineEdit* filesEdit;
    QPushButton* selectFilesButton;
    QGroupBox* filesGroup;

    QCheckBox* apeCheck;
    QCheckBox* asfCheck;
    QCheckBox* id3v1Check;
    QCheckBox* id3v2Check;
    QCheckBox* infoTagCheck;
    QCheckBox* xiphCommentCheck;
    QGroupBox* tagsGroup;

    QCheckBox* titleCheck;
    QCheckBox* trackCheck;
    QCheckBox* albumCheck;
    QCheckBox* artistCheck;
    QCheckBox* genreCheck;
    QCheckBox* yearCheck;
    QCheckBox* commentCheck;
    QLineEdit* titleEdit;
    QLineEdit* trackEdit;
    QLineEdit* albumEdit;
    QLineEdit* artistEdit;
    Id3GenreSelection* genreEdit;
    QLineEdit* yearEdit;
    QLineEdit* commentEdit;
    QGroupBox* editorGroup;

    QPushButton* okButton;
    QPushButton* cancelButton;

    FileList* fileList;
    QStringList listOfFiles;

    void createLayout();
    void saveTagsTo(QString nameOfTag, QString path);

private slots:
    void startTagging();
    void openFiles();

};

#endif // MULTIPLETAGGINGDIALOG_H
