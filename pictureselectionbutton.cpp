#include "pictureselectionbutton.h"

PictureSelectionButton::PictureSelectionButton(QWidget* parent) : QPushButton("Select a picture...", parent) {

    QObject::connect(this, SIGNAL(clicked()), this, SLOT(selectPicture()));
    picturePath = new QString();

}

PictureSelectionButton::~PictureSelectionButton() {
    delete picturePath;
}

void PictureSelectionButton::selectPicture() {

    QFileDialog dialog(this);
    dialog.setOption(QFileDialog::DontUseNativeDialog);
#ifdef WIN32
    dialog.setDirectory("C:/");
#else
    dialog.setDirectory("/home");
#endif
    dialog.setNameFilter("Images (*.jpeg *.jpg *.png)");
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.show();
    if(dialog.exec()) {
        QStringList nameList = dialog.selectedFiles();
        QString name = nameList.join("");
        picturePath->clear();
        picturePath->append(name);
    }

}

QString* PictureSelectionButton::getPicturePath() {
    return picturePath;
}

