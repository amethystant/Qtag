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

#include "coverartactions.h"
#include <QSettings>
#include <QMessageBox>
#include <QScrollArea>
#include <QFileDialog>
#include <QHBoxLayout>

CoverArtActions::CoverArtActions(QWidget *parent, QLabel *preview) : QObject(parent) {

    this->parent = parent;
    picturePreview = preview;

}

void CoverArtActions::showPicturePreview(QImage image) {

    QSettings settings;
    int size = settings.value("previewsize", QVariant(150)).toInt();
    if(image.isNull()) {
        picturePreview->clear();
        picturePreview->setPixmap(QPixmap::fromImage(QImage(":images/nofile.png")));
    } else {
        image = image.scaled(size, size);
        picturePreview->clear();
        picturePreview->setPixmap(QPixmap::fromImage(image));
    }
    picturePreview->update();

}

void CoverArtActions::savePictureAsFile(QImage image) {

    if(image.isNull()) {
        QMessageBox::warning(parent, "Warning", "There is no picture to save.");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(parent, "Save cover", 0, "PNG Images (*.png)");
    image.save(fileName);

}

void CoverArtActions::showPictureFullSize(QImage image) {

    if(image.isNull()) {
        QMessageBox::warning(parent, "Error", "There is no picture to show.");
        return;
    }

    QDialog* dialog = new QDialog(parent);
    QScrollArea* scrollArea = new QScrollArea();
    QLabel* preview = new QLabel(scrollArea);
    preview->setPixmap(QPixmap::fromImage(image));
    scrollArea->setWidget(preview);
    QHBoxLayout* l = new QHBoxLayout(dialog);
    l->addWidget(scrollArea);
    dialog->setLayout(l);
    dialog->setWindowTitle("Cover art");
    dialog->show();

}
