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

#ifndef COMMONTAGEDITOR_H
#define COMMONTAGEDITOR_H

#include "tageditor.h"
#include "tag.h"

/*
 * An implementation of the TagEditor class, which is common to all tags
 * that don't specify a fixed list of genres.
*/
class CommonTagEditor : public TagEditor {

    Q_OBJECT

public:
    CommonTagEditor(TagLib::Tag* tag, QString nameOfTag, QWidget* parent);

private:
    QLabel* genreLabel;
    QLineEdit* genreEdit;

protected:
    virtual void createLayout();

protected slots:
    virtual void updateTags();

};

#endif // COMMONTAGEDITOR_H
