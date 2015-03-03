#ifndef ID3GENRESELECTION_H
#define ID3GENRESELECTION_H

#include <QComboBox>

/*
A class derived from QComboBox, which contains the list of ID3 genres
*/
class Id3GenreSelection : public QComboBox {
public:
    Id3GenreSelection(QWidget *parent);
};

#endif
