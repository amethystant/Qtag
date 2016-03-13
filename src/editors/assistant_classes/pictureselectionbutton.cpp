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

#include <QSettings>
#include "editors/assistant_classes/pictureselectionbutton.h"

PictureSelectionButton::PictureSelectionButton(QWidget* parent, QString* path, QLabel* preview) : QPushButton("Select a picture...", parent) {

    QObject::connect(this, SIGNAL(clicked()), this, SLOT(selectPicture()));
    picturePath = path;
    picturePreview = preview;

}

void PictureSelectionButton::selectPicture() {

    QFileDialog dialog(this);
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
        QSettings settings;
        int size = settings.value("previewsize", 150).toInt();
        image = image.scaled(size, size);
        picturePath->clear();
        picturePath->append(name);
        picturePreview->setPixmap(QPixmap::fromImage(image));
        emit pictureChanged();

    }

}

