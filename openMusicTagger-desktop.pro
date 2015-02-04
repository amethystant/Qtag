#-------------------------------------------------
#
# Project created by QtCreator 2015-01-28T17:03:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = openMusicTagger-desktop
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    audiofile.cpp

HEADERS  += mainwindow.h \
    audiofile.h

FORMS    += mainwindow.ui

RESOURCES += \
    qdarkstyle/style.qrc \
    images.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/lib/release/ -ltag
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/lib/debug/ -ltag
else:unix: LIBS += -L$$PWD/../../../../usr/lib/ -ltag

INCLUDEPATH += $$PWD/../../../../usr/include
DEPENDPATH += $$PWD/../../../../usr/include
