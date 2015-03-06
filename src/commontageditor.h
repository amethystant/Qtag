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
