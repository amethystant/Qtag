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

#include "editors/assistant_classes/coverartactions.h"
#include <QSettings>
#include <QMessageBox>
#include <QScrollArea>
#include <QFileDialog>
#include <QHBoxLayout>

CoverArtActions::CoverArtActions(QWidget *parent, QLabel *preview) : QObject(parent) {

    this->parent = parent;
    picturePreview = preview;

}

void CoverArtActions::showPicturePreview(QImage* image) {

    QSettings settings;
    int size = settings.value("previewsize", QVariant(150)).toInt();
    if(!image || image->isNull()) {
        picturePreview->clear();
        picturePreview->setPixmap(QPixmap::fromImage(QImage(":images/nofile.png")));
    } else {
        QImage scaledImage = image->scaled(size, size);
        picturePreview->clear();
        picturePreview->setPixmap(QPixmap::fromImage(scaledImage));
    }
    picturePreview->update();

}

void CoverArtActions::savePictureAsFile(QImage* image) {

    if(!image || image->isNull()) {
        QMessageBox::warning(parent, "Warning", "There is no picture to save.");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(parent, "Save cover", 0, "PNG Images (*.png)");
    image->save(fileName);

}

void CoverArtActions::showPictureFullSize(QImage* image) {

    if(!image || image->isNull()) {
        QMessageBox::warning(parent, "Error", "There is no picture to show.");
        return;
    }

    QDialog* dialog = new QDialog(parent);
    QScrollArea* scrollArea = new QScrollArea();
    QLabel* preview = new QLabel(scrollArea);
    preview->setPixmap(QPixmap::fromImage(*image));
    scrollArea->setWidget(preview);
    QHBoxLayout* l = new QHBoxLayout(dialog);
    l->addWidget(scrollArea);
    dialog->setLayout(l);
    dialog->setWindowTitle("Cover art");
    dialog->show();

}
