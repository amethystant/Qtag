/*
 *    Qtag is an advanced but simple to use audio metadata editor. Runs on Linux
 *    and Windows. Supports many formats, including MPEG, Ogg Vorbis, Wave and FLAC
 *
 *    Copyright (C) 2015 - 2016  Karel Patlejch <kaja.patlejch@gmail.com>
 *
 *    Used libraries:
 *      TagLib - http://taglib.github.io/
 *      Qt - http://qt.io
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License along
 *    with this program; if not, write to the Free Software Foundation, Inc.,
 *    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef MULTIPLETAGGINGDIALOG_H
#define MULTIPLETAGGINGDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QCheckBox>
#include <QRadioButton>
#include "core/audiofile.h"
#include "editors/assistant_classes/id3genreselection.h"
#include "core/filelist.h"

class MultipleTaggingDialog : public QDialog {

    Q_OBJECT

public:
    MultipleTaggingDialog(QWidget* parent, FileList *list, QList<AudioFile*>* selectedFiles);

private:
    QLabel* filesLabel;
    QLineEdit* filesEdit;
    QRadioButton* useNewFilesButton;
    QRadioButton* useSelectedFilesButton;
    QPushButton* selectFilesButton;
    QGroupBox* filesGroup;

    QRadioButton* multipleTaggingButton;
    QRadioButton* duplicateTagsButton;
    QGroupBox* operationGroup;

    QLabel* sourceTagLabel;
    QComboBox* sourceTagBox;
    QGroupBox* duplicateTagsGroup;

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
    QCheckBox* coverCheck;
    QLineEdit* titleEdit;
    QLineEdit* trackEdit;
    QLineEdit* albumEdit;
    QLineEdit* artistEdit;
    Id3GenreSelection* genreEdit;
    QLineEdit* yearEdit;
    QLineEdit* commentEdit;
    QLineEdit* coverEdit;
    QPushButton* selectCoverButton;
    QGroupBox* editorGroup;

    QPushButton* okButton;
    QPushButton* cancelButton;

    QList<AudioFile*>* selectedFiles;
    FileList* fileList;
    QStringList listOfFiles;

    QString coverEditDefaultText;

    void createLayout();

private slots:
    void startTagging();
    void openFiles();
    void selectCover();
    void selectOperation();

};

#endif // MULTIPLETAGGINGDIALOG_H
