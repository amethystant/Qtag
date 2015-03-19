#ifndef MULTIPLETAGGINGDIALOG_H
#define MULTIPLETAGGINGDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QCheckBox>
#include "id3genreselection.h"

class MultipleTaggingDialog : public QDialog {

    Q_OBJECT

public:
    MultipleTaggingDialog(QWidget* parent);

private:
    QLabel* filesLabel;
    QLineEdit* filesEdit;
    QPushButton* selectFilesButton;
    QGroupBox* filesGroup;

    QCheckBox* apeCheck;
    QCheckBox* asfCheck;
    QCheckBox* id3v1Check;
    QCheckBox* id3v2Check;
    QCheckBox* infoTagCheck;
    QCheckBox* xiphCommentCheck;
    QGroupBox* tagsGroup;

    QCheckBox* titleCheck;
    QCheckBox* trackCheck;
    QCheckBox* albumCheck;
    QCheckBox* artistCheck;
    QCheckBox* genreCheck;
    QCheckBox* yearCheck;
    QCheckBox* commentCheck;
    QLineEdit* titleEdit;
    QLineEdit* trackEdit;
    QLineEdit* albumEdit;
    QLineEdit* artistEdit;
    Id3GenreSelection* genreEdit;
    QLineEdit* yearEdit;
    QLineEdit* commentEdit;
    QGroupBox* editorGroup;

    QPushButton* okButton;
    QPushButton* cancelButton;

    QStringList listOfFiles;

    void createLayout();
    void saveTagsTo(QString nameOfTag, QString path);

private slots:
    void startTagging();
    void openFiles();

};

#endif // MULTIPLETAGGINGDIALOG_H
