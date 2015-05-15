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

#include "pictureselectionbutton.h"

PictureSelectionButton::PictureSelectionButton(QWidget* parent, QString* path, QLabel* preview) : QPushButton("Select a picture...", parent) {

    QObject::connect(this, SIGNAL(clicked()), this, SLOT(selectPicture()));
    picturePath = path;
    picturePreview = preview;

}

PictureSelectionButton::~PictureSelectionButton() {
    delete picturePath;
}

void PictureSelectionButton::selectPicture() {

    QFileDialog dialog(this);
    dialog.setOption(QFileDialog::DontUseNativeDialog);
#ifdef WIN32
    dialog.setDirectory("C:/");
#else
    dialog.setDirectory("/home");
#endif
    dialog.setNameFilter("Images (*.jpeg *.jpg *.png)");
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.show();
    if(dialog.exec()) {
        QStringList nameList = dialog.selectedFiles();
        QString name = nameList.join("");
        QImage image(name);
        image = image.scaled(100, 100);
        picturePath->clear();
        picturePath->append(name);
        picturePreview->setPixmap(QPixmap::fromImage(image));
        emit pictureChanged();

    }

}

