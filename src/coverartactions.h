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

#ifndef COVERARTVIEWACTIONS_H
#define COVERARTVIEWACTIONS_H

#include <QObject>
#include <QLabel>

class CoverArtActions : public QObject {

    Q_OBJECT

public:
    CoverArtActions(QWidget *parent, QLabel *preview);
    void showPicturePreview(QImage image);
    void savePictureAsFile(QImage image);
    void showPictureFullSize(QImage image);

private:
    QWidget* parent;
    QLabel* picturePreview;

};

#endif // COVERARTVIEWACTIONS_H
