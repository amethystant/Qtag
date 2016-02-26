#    Qtag is an advanced but simple to use audio metadata editor. Runs on Linux
#    and Windows. Supports many formats, including MPEG, Ogg Vorbis, Wave and FLAC
#
#    Copyright (C) 2015 - 2016  Karel Patlejch <kaja.patlejch@gmail.com>
#
#    Used libraries:
#      TagLib - http://taglib.github.io/
#      Qt - http://qt.io
#
#    This program is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License along
#    with this program; if not, write to the Free Software Foundation, Inc.,
#    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

SOURCES += core/main.cpp                                        \
    core/mainwindow.cpp                                         \
    core/audiofile.cpp                                          \
    core/tageditorlayout.cpp                                    \
    editors/tageditor.cpp                                       \
    editors/id3v1editor.cpp                                     \
    editors/assistant_classes/id3genreselection.cpp             \
    editors/id3v2editor.cpp                                     \
    editors/assistant_classes/pictureselectionbutton.cpp        \
    core/picturefile.cpp                                        \
    editors/commontageditor.cpp                                 \
    dialogs/copytagsdialog.cpp                                  \
    dialogs/multipletaggingdialog.cpp                           \
    dialogs/createalbumdialog.cpp                               \
    core/filelist.cpp                                           \
    dialogs/configdialog.cpp                                    \
    editors/assistant_classes/coverartactions.cpp               \
    core/qtagapp.cpp                                            \
    core/audiotag.cpp                                           \
    actions/actions.cpp

HEADERS += core/picturefile.h                                   \
    editors/id3v2editor.h                                       \
    editors/id3v1editor.h                                       \
    core/mainwindow.h                                           \
    core/audiofile.h                                            \
    core/tageditorlayout.h                                      \
    editors/tageditor.h                                         \
    core/main.h                                                 \
    editors/assistant_classes/id3genreselection.h               \
    editors/assistant_classes/pictureselectionbutton.h          \
    editors/commontageditor.h                                   \
    dialogs/copytagsdialog.h                                    \
    dialogs/multipletaggingdialog.h                             \
    dialogs/createalbumdialog.h                                 \
    core/filelist.h                                             \
    dialogs/configdialog.h                                      \
    editors/assistant_classes/coverartactions.h                 \
    core/qtagapp.h                                              \
    core/audiotag.h                                             \
    actions/actions.h

FORMS += ui/mainwindow.ui

RESOURCES += images/images.qrc \
    text_files/text_files.qrc



unix:!android {

    TARGET = qtag

    LIBS += -L/usr/lib -L/usr/local/lib -L/usr/lib/x86_64-linux-gnu -ltag -lz

    INCLUDEPATH += /usr/include/taglib \
                    /usr/local/include/taglib

    DEPENDPATH += /usr/include/taglib \
                    /usr/local/include/taglib

    binary.path = /usr/local/bin
    binary.files = qtag

    desktopfile.path = ~/.local/share/applications
    desktopfile.files = qtag.desktop

    pixmap.path = ~/.local/share/pixmaps
    pixmap.files = images/Qtag.png

    INSTALLS += binary desktopfile pixmap

}

android {

    TARGET = Qtag

    LIBS += -L/usr/arm-linux-androideabi/lib -L/usr/i686-linux-androideabi/lib/ -ltag

    INCLUDEPATH += /usr/arm-linux-androideabi/include/taglib \
                    /usr/i686-linux-androideabi/include/taglib

    DEPENDPATH += /usr/arm-linux-androideabi/include/taglib \
                    /usr/i686-linux-androideabi/include/taglib

    ANDROID_EXTRA_LIBS += /usr/arm-linux-androideabi/lib/libtag.so \
                            /usr/i686-linux-androideabi/lib/libtag.so

    DISTFILES += \
        android/AndroidManifest.xml \
        android/gradle/wrapper/gradle-wrapper.jar \
        android/gradlew \
        android/res/values/libs.xml \
        android/build.gradle \
        android/gradle/wrapper/gradle-wrapper.properties \
        android/gradlew.bat

    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

}

win32 {

    TARGET = Qtag

    LIBS += -L"C:\Libraries\taglib\lib" -ltag
    INCLUDEPATH += C:/Libraries/taglib/include/taglib
    DEPENDPATH += C:/Libraries/taglib/include/taglib

    CONFIG += static

    RC_ICONS = Qtag.ico
    target.path = "C:/Program Files/Qtag"

}

