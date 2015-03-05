#ifndef APETAGEDITOR_H
#define APETAGEDITOR_H

#include "tageditor.h"
#include "apetag.h"
#include "QLabel"
#include "QLineEdit"

class ApeTagEditor : public TagEditor {

    Q_OBJECT

public:
    ApeTagEditor(TagLib::APE::Tag* tag, QWidget* parent);

private:
    TagLib::APE::Tag* apeTag;
    QLabel* genreLabel;
    QLineEdit* genreEdit;

protected:
    virtual void createLayout();

protected slots:
    virtual void updateTags();

};

#endif // APETAGEDITOR_H
