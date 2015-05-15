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

#ifndef PICTURESELECTIONBUTTON_H
#define PICTURESELECTIONBUTTON_H

#include <QPushButton>
#include <QFileDialog>
#include <QStringList>
#include <QLabel>

class PictureSelectionButton : public QPushButton {

    Q_OBJECT

public:
    PictureSelectionButton(QWidget *parent, QString* path, QLabel* preview);
    ~PictureSelectionButton();

private:
    QString *picturePath;
    QLabel *picturePreview;

signals:
    void pictureChanged();

public slots:
    void selectPicture();

};

#endif // PICTURESELECTIONBUTTON_H
