#ifndef TAGEDITOR_H
#define TAGEDITOR_H

#include <QtWidgets>
#include <tag.h>
#include "main.h"
#include <fileref.h>

/*
The base class for all tag editors (e.g. ID3v1 editor, XiphComment editor,...).
Contains all the common widgets and a method to save the tags
*/

class TagEditor : public QGroupBox {

    Q_OBJECT

public:
    TagEditor(TagLib::Tag* tag, QString nameOfTag, QWidget *parent);

protected:
    TagLib::Tag* tag;
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
    virtual void createLayout();

protected slots:
    virtual void updateTags();

signals:
    void fileEdited();

};

#endif // TAGEDITOR_H
