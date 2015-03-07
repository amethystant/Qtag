#ifndef APETAGEDITOR_H
#define APETAGEDITOR_H

#include "tageditor.h"
#include "apetag.h"
#include "commontageditor.h"
#include "QLabel"
#include "QLineEdit"

class ApeTagEditor : public CommonTagEditor {

    Q_OBJECT

public:
    ApeTagEditor(TagLib::APE::Tag* tag, QWidget* parent);

private:
    TagLib::APE::Tag* apeTag;

protected:
    virtual void createLayout();

protected slots:
    virtual void updateTags();

};

#endif // APETAGEDITOR_H
