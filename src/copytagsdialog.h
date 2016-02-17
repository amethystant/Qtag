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
