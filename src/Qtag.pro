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

SOURCES += main.cpp \
    mainwindow.cpp \
    audiofile.cpp \
    tageditorlayout.cpp \
    tageditor.cpp \
    id3v1editor.cpp \
    id3genreselection.cpp \
    id3v2editor.cpp \
    pictureselectionbutton.cpp \
    picturefile.cpp \
    commontageditor.cpp \
    copytagsdialog.cpp \
    multipletaggingdialog.cpp \
    createalbumdialog.cpp \
    filelist.cpp \
    configdialog.cpp \
    coverartactions.cpp

HEADERS += picturefile.h \
    id3v2editor.h \
    id3v1editor.h \
    mainwindow.h \
    audiofile.h \
    tageditorlayout.h \
    tageditor.h \
    main.h \
    id3genreselection.h \
    pictureselectionbutton.h \
    commontageditor.h \
    copytagsdialog.h \
    multipletaggingdialog.h \
    createalbumdialog.h \
    filelist.h \
    configdialog.h \
    coverartactions.h

FORMS += mainwindow.ui

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

