#ifndef ID3V1EDITOR_H
#define ID3V1EDITOR_H

#include "tageditor.h"
#include "id3v1tag.h"
#include "id3genreselection.h"

class Id3v1Editor : public TagEditor {

    Q_OBJECT

public:
    Id3v1Editor(TagLib::FileRef* file, QWidget* parent);
    ~Id3v1Editor();

private:
    Id3GenreSelection* genreEdit;
    QLabel* genreLabel;

protected:
    virtual void createLayout();

protected slots:
    virtual void saveTags();
};

#endif // ID3V1EDITOR_H
