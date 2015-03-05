#ifndef ID3V2EDITOR_H
#define ID3V2EDITOR_H

#include <id3v2tag.h>
#include <attachedpictureframe.h>
#include "pictureselectionbutton.h"
#include "picturefile.h"
#include "tageditor.h"
#include "id3genreselection.h"

class Id3v2Editor : public TagEditor {

    Q_OBJECT

public:
    Id3v2Editor(TagLib::ID3v2::Tag *tag, QWidget *parent);

private:
    TagLib::ID3v2::Tag* id3v2Tag;
    Id3GenreSelection* genreEdit;
    QLabel* genreLabel;
    QString* picturePath;
    PictureSelectionButton* pictureSelection;
    QPushButton* removeCoverButton;
    QLabel* picturePreview;
    QLabel* pictureLabel;
    void extractPictureFromTag();

protected:
    virtual void createLayout();

protected slots:
    virtual void updateTags();

private slots:
    void removeCover();

};

#endif // ID3V2EDITOR_H
