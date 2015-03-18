#ifndef COPYTAGSDIALOG_H
#define COPYTAGSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include "audiofile.h"
#include <string>

class CopyTagsDialog : public QDialog {

    Q_OBJECT

public:
    CopyTagsDialog(QWidget *parent, QList<AudioFile *> *listOfFiles);

private:
    QList<AudioFile*> *listOfFiles;
    QLabel* sourceFileLabel;
    QLabel* sourceTagLabel;
    QLabel* targetFileLabel;
    QLabel* targetTagLabel;
    QComboBox* sourceFileSelection;
    QComboBox* sourceTagSelection;
    QComboBox* targetFileSelection;
    QComboBox* targetTagSelection;
    QPushButton* okButton;
    QPushButton* cancelButton;
    void createLayout();
    void initComboBoxes();
    void copyTags(TagLib::Tag* sourceTag, TagLib::Tag* targetTag);

private slots:
    void startCopying();
    void updateComboBoxes();

};

#endif // COPYTAGSDIALOG_H
