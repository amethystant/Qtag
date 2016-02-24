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

#ifndef TAGEDITORLAYOUT_H
#define TAGEDITORLAYOUT_H

#include <QtWidgets>
#include <sstream>
#include "core/main.h"

class MainWindow;
class AudioFile;
class AudioTag;


/*
A class representing the layout of all tag editors for a file.
It recognizes which tags are being in the file and generates tag
editors (objects of classes derived from the TagEditor class).
Once a file is selected to be edited, the dockable widget on the left is updated
and it sets the file's TagEditorLayout as the layout.
*/
class TagEditorLayout : public QVBoxLayout {
    Q_OBJECT

public:
    explicit TagEditorLayout(MainWindow* window, AudioFile *file);
    AudioFile* getFile();

private:
    MainWindow* window;
    AudioFile* file;
    QWidget* parent; //this widget is the parent of all the widgets in this layout
    void loadTagEditors();
    void loadAsfTags();
    void loadWavPackTags();
    void loadMpegTags();
    void loadFlacTags();
    void loadWavTags();
    void loadOggVorbisTags();
    void addId3v1Editor();
    void addId3v2Editor();
    void addApeTagEditor();
    void addXiphCommentEditor();
    AudioTag *apeTag;
    AudioTag *asfTag;
    AudioTag *id3v1Tag;
    AudioTag *id3v2Tag;
    AudioTag *infoTag;
    AudioTag *xiphComment;

};

#endif // TAGEDITORLAYOUT_H
