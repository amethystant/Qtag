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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QtCore>
#include <QSpacerItem>

#include "core/audiofile.h"
#include "core/tageditorlayout.h"
#include "core/filelist.h"

class QtagApp;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    explicit MainWindow(QtagApp* app);
    ~MainWindow();
    Ui::MainWindow* getUI();

private:
    Ui::MainWindow *ui;
    QtagApp* app;
    FileList* listOfFiles;

    /*
     * List of all tag editor layouts. When the user clicks to open a file in the editor,
     * a TagEditorLayout pointer is created and added to this list.
    */
    QList<TagEditorLayout*> listOfLayouts;

    TagEditorLayout* findLayout(AudioFile* file, bool create = true);
    void setIcons();
    void closeEditor();
    bool unsavedChanges();
    void saveSession();
    void openLastSession();
    void updateViews();
    void updateEditor();
    AudioFile* openedFile; //the file that is viewed in the tag editor
    QSpacerItem* spacer;

public slots:
    void openFileDialog();
    void openDirectory();
    void openInEditor(QTreeWidgetItem* file);
    void saveAll();
    void closeAll();
    void openCopyTagsDialog();
    void closeCurrentFile();
    void saveCurrentFile();
    void openMultipleTaggingDialog();
    void openCreateAlbumDialog();
    void updateWindowTitle();
    void openSettingsDialog();
    void openAboutDialog();
    void openLicenseDialog();
    void fileListChangeUpdate();

};

#endif // MAINWINDOW_H
