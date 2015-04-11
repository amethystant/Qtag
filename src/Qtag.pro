QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qtag
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
    createalbumdialog.cpp

HEADERS  += picturefile.h \
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
    createalbumdialog.h


FORMS    += mainwindow.ui

RESOURCES += images/images.qrc

unix: LIBS += -L/usr/lib/ -ltag
win32: LIBS += -L"C:\Libraries\taglib\lib" -ltag

unix:INCLUDEPATH +=/usr/include/taglib
unix:DEPENDPATH += /usr/include/taglib
win32:INCLUDEPATH += C:/Libraries/taglib/include/taglib
win32:DEPENDPATH += C:/Libraries/taglib/include/taglib
