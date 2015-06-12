#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
#
# (C) 2015 by Karel Patlejch
#
# Used libraries:
#    TagLib - https://github.com/taglib
#    Qt - http://qt.io
#
#

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

SOURCES += main.cpp\
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
    configdialog.cpp

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
    configdialog.h

FORMS += mainwindow.ui

RESOURCES += images/images.qrc \
    text_files/text_files.qrc

unix {

    TARGET = qtag

    LIBS += -L/usr/lib/ -ltag
    INCLUDEPATH +=/usr/include/taglib
    DEPENDPATH += /usr/include/taglib

    binary.path = /usr/local/bin
    binary.files = qtag

    desktopfile.path = ~/.local/share/applications
    desktopfile.files = qtag.desktop

    pixmap.path = ~/.local/share/pixmaps
    pixmap.files = images/Qtag.png

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

INSTALLS += binary desktopfile pixmap
