#ifndef TAGEDITOR_H
#define TAGEDITOR_H

#include <QtWidgets>
#include <tag.h>
#include "main.h"

class TagEditor : public QObject {

    Q_OBJECT

public:
    TagEditor(TagLib::Tag* tag, QString nameOfTag, QWidget* parent);
    ~TagEditor();

private:
    TagLib::Tag* tag;
    QGroupBox* editorBox;
    QLabel* nameLabel;
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

private slots:
    void saveTags();

};

#endif // TAGEDITOR_H
