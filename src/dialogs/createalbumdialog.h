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

#ifndef CREATEALBUMDIALOG_H
#define CREATEALBUMDIALOG_H

#include <QCheckBox>
#include <QDialog>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "core/audiofile.h"
#include "core/filelist.h"

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
