QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtag
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

    LIBS += -L/usr/lib/ -ltag
    INCLUDEPATH +=/usr/include/taglib
    DEPENDPATH += /usr/include/taglib

    target.path = /usr/local/bin
    target.commands += "install -m 755 -p "qtag" "/usr/local/bin/qtag"; \
        cp images/Qtag.png /usr/share/pixmaps; \
        cp qtag.desktop /usr/share/applications"

}

win32 {

    LIBS += -L"C:\Libraries\taglib\lib" -ltag
    INCLUDEPATH += C:/Libraries/taglib/include/taglib
    DEPENDPATH += C:/Libraries/taglib/include/taglib

    RC_ICONS = Qtag.ico
    target.path = "C:/Program Files/Qtag"

}

INSTALLS += target
