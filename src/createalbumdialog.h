#ifndef CREATEALBUMDIALOG_H
#define CREATEALBUMDIALOG_H

#include <QCheckBox>
#include <QDialog>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "audiofile.h"

class CreateAlbumDialog : public QDialog {

    Q_OBJECT

public:
    CreateAlbumDialog(QWidget* parent);

private:
    QLabel* directoryLabel;
    QLineEdit* directoryEdit;
    QPushButton* directorySelectionButton;
    QGroupBox* directoryGroup;

    QLabel* tagFormatLabel;
    QLineEdit* tagFormatEdit;
    QPushButton* hintButton;
    QGroupBox* tagFormatGroup;

    QCheckBox* makeCapitalLettersCheck;
    QLabel* replaceStringLabel;
    QLineEdit* replaceStringEdit;
    QLabel* replaceByLabel;
    QLineEdit* replaceByEdit;
    QGroupBox* additionalChangesGroup;

    QCheckBox* apeCheck;
    QCheckBox* asfCheck;
    QCheckBox* id3v1Check;
    QCheckBox* id3v2Check;
    QCheckBox* infoTagCheck;
    QCheckBox* xiphCommentCheck;
    QGroupBox* tagsGroup;

    QPushButton* startTaggingButton;
    QPushButton* cancelButton;

    void createLayout();
    void tagFormatError();
    void saveTagsTo(AudioFile* f, std::string nameOfTag,
                    QString title, QString track, QString album, QString artist);

private slots:
    void openDirectorySelection();
    void showHint();
    void startTagging();

};

#endif // CREATEALBUMDIALOG_H
