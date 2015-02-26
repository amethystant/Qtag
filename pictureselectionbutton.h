#ifndef PICTURESELECTIONBUTTON_H
#define PICTURESELECTIONBUTTON_H

#include <QPushButton>
#include <QFileDialog>
#include <QStringList>

class PictureSelectionButton : public QPushButton {

    Q_OBJECT

public:
    PictureSelectionButton(QWidget *parent);
    ~PictureSelectionButton();
    QString* getPicturePath();

private:
    QString *picturePath;

public slots:
    void selectPicture();

};

#endif // PICTURESELECTIONBUTTON_H
