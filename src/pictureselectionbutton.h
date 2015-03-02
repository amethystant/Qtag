#ifndef PICTURESELECTIONBUTTON_H
#define PICTURESELECTIONBUTTON_H

#include <QPushButton>
#include <QFileDialog>
#include <QStringList>
#include <QLabel>

class PictureSelectionButton : public QPushButton {

    Q_OBJECT

public:
    PictureSelectionButton(QWidget *parent, QString* path, QLabel* preview);
    ~PictureSelectionButton();

private:
    QString *picturePath;
    QLabel *picturePreview;

public slots:
    void selectPicture();

};

#endif // PICTURESELECTIONBUTTON_H
