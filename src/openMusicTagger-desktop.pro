QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = openMusicTagger-desktop
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
    picturefile.cpp

HEADERS  += picturefile.h \
    id3v2editor.h \
    id3v1editor.h \
    mainwindow.h \
    audiofile.h \
    tageditorlayout.h \
    tageditor.h \
    main.h \
    id3genreselection.h \
    pictureselectionbutton.h


FORMS    += mainwindow.ui

RESOURCES += \
    qdarkstyle/style.qrc \
    images/images.qrc

win32:CONFIG(release, debug|release): LIBS += -ltag
else:win32:CONFIG(debug, debug|release): LIBS += -ltag
else:unix: LIBS += -L/usr/lib/ -ltag

INCLUDEPATH +=/usr/include/taglib
DEPENDPATH += /usr/include/taglib
