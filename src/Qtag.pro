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

unix {

    !android: TARGET = qtag
    android: TARGET = Qtag

    LIBS += -L/usr/lib/ -L/usr/arm-linux-androideabi/lib -L/usr/i686-linux-androideabi/lib/ -ltag

    INCLUDEPATH += /usr/include/taglib \
                    /usr/arm-linux-androideabi/include/taglib \
                    /usr/i686-linux-androideabi/include/taglib

    DEPENDPATH += /usr/include/taglib \
                    /usr/arm-linux-androideabi/include/taglib \
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


    !android {
        binary.path = /usr/local/bin
        binary.files = qtag

        desktopfile.path = ~/.local/share/applications
        desktopfile.files = qtag.desktop

        pixmap.path = ~/.local/share/pixmaps
        pixmap.files = images/Qtag.png

        INSTALLS += binary desktopfile pixmap
    }

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

