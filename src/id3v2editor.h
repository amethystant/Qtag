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

#ifndef ID3V2EDITOR_H
#define ID3V2EDITOR_H

#include <QImage>
#include <id3v2tag.h>
#include <attachedpictureframe.h>
#include "pictureselectionbutton.h"
#include "picturefile.h"
#include "tageditor.h"
#include "id3genreselection.h"
#include "coverartactions.h"

class Id3v2Editor : public TagEditor {

    Q_OBJECT

public:
    Id3v2Editor(TagLib::ID3v2::Tag *tag, QWidget *parent);
    ~Id3v2Editor();

private:
    TagLib::ID3v2::Tag* id3v2Tag;
    Id3GenreSelection* genreEdit;
    QLabel* genreLabel;
    QString* picturePath;
    PictureSelectionButton* pictureSelection;
    QPushButton* removeCoverButton;
    QPushButton* extractPictureButton;
    QPushButton* pictureFullSizeButton;
    QLabel* picturePreview;
    QLabel* pictureLabel;
    QImage getPictureFromTag();
    CoverArtActions* coverArtActions;

protected:
    virtual void createLayout();

protected slots:
    virtual void updateTags();

private slots:
    void removeCover();
    void showPictureFullSize();
    void savePictureAsFile();

};

#endif // ID3V2EDITOR_H
