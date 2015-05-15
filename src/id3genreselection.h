/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 *
 * (C) 2015 by Karel Patlejch
 *
 * Used libraries:
 *    TagLib - https://github.com/taglib
 *    Qt - http://qt.io
 *
*/

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
