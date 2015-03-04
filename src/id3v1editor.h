#ifndef ID3V1EDITOR_H
#define ID3V1EDITOR_H

#include <id3v1tag.h>
#include "id3genreselection.h"
#include <tageditor.h>

/*
The Id3v1 implementation of TagEditor class
*/
class Id3v1Editor : public TagEditor {

    Q_OBJECT

public:
    Id3v1Editor(TagLib::ID3v1::Tag* tag, QWidget *parent);

private:
    TagLib::ID3v1::Tag* id3v1Tag;
    Id3GenreSelection* genreEdit;
    QLabel* genreLabel;

protected:
    virtual void createLayout();

protected slots:
    virtual void updateTags();
};

#endif // ID3V1EDITOR_H
