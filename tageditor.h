#ifndef TAGEDITOR_H
#define TAGEDITOR_H

#include <QtWidgets>
#include <tag.h>
#include "main.h"
#include <fileref.h>

/*
The base class for all tag editors (e.g. ID3v1 editor, XiphComment Editor,...).
Contains all the common widgets and a method to save the tags
*/

class TagEditor : public QObject {

    Q_OBJECT

public:
    TagEditor(TagLib::FileRef* file, QString nameOfTag, QWidget* parent);
    ~TagEditor();

protected:
    TagLib::FileRef* file;
    TagLib::Tag* tag;
    QGroupBox* editorBox;
    QGridLayout* layout;
    QLabel* titleLabel;
    QLabel* trackLabel;
    QLabel* albumLabel;
    QLabel* artistLabel;
    QLabel* commentLabel;
    QLabel* yearLabel;
    QLineEdit* titleEdit;
    QLineEdit* trackEdit;
    QLineEdit* albumEdit;
    QLineEdit* artistEdit;
    QLineEdit* commentEdit;
    QLineEdit* yearEdit;
    QPushButton* saveButton;
    virtual void createLayout();

protected slots:
    virtual void saveTags();

};

#endif // TAGEDITOR_H
