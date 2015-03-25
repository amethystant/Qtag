#ifndef CREATEALBUMDIALOG_H
#define CREATEALBUMDIALOG_H

#include <QCheckBox>
#include <QDialog>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

class CreateAlbumDialog : public QDialog {

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

    void createLayout();

private slots:
    void startTagging();
    void openFiles();

};

#endif // CREATEALBUMDIALOG_H
