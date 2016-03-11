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

#ifndef QTAGAPP_H
#define QTAGAPP_H

#include <QApplication>
#include <QStyle>
#include "core/filelist.h"
#include "core/mainwindow.h"

/*
 * This class is NOT inherited from QApplication and has
 * not the same purpose. While QApplication controls the application loop,
 * this class only holds some basic variables and methods for handling files
 * and the UI.
 */

class QtagApp : public QObject {

    Q_OBJECT

public:
    QtagApp(QApplication* app);
    void start();
    void openFile(QString path, bool update = true);
    void closeFile(QString path, bool update = true);
    void closeFile(int i, bool update = true);
    FileList* getFileList();
    static QStyle* getStyleFromSettings();

private:
    MainWindow* window;
    FileList* fileList;
    void openFilesFromArguments(QStringList files);
    void openLastSession();

private slots:
    void saveSession();

signals:
    void fileListChanged();

};

#endif // QTAGAPP_H
