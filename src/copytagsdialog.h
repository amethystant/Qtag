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

#ifndef COPYTAGSDIALOG_H
#define COPYTAGSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include "audiofile.h"
#include "filelist.h"
#include <string>

class CopyTagsDialog : public QDialog {

    Q_OBJECT

public:
    CopyTagsDialog(QWidget *parent, FileList *listOfFiles);

private:
    FileList* listOfFiles;
    QLabel* sourceFileLabel;
    QLabel* sourceTagLabel;
    QLabel* targetFileLabel;
    QLabel* targetTagLabel;
    QComboBox* sourceFileSelection;
    QComboBox* sourceTagSelection;
    QComboBox* targetFileSelection;
    QComboBox* targetTagSelection;
    QPushButton* okButton;
    QPushButton* cancelButton;
    AudioFile* sourceFile;
    AudioFile* targetFile;
    void createLayout();
    void initComboBoxes();
    void copyTags(TagLib::Tag* sourceTag, TagLib::Tag* targetTag);

private slots:
    void startCopying();
    void updateComboBoxes();

};

#endif // COPYTAGSDIALOG_H
