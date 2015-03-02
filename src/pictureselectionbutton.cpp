#include "pictureselectionbutton.h"

PictureSelectionButton::PictureSelectionButton(QWidget* parent, QString* path, QLabel* preview) : QPushButton("Select a picture...", parent) {

    QObject::connect(this, SIGNAL(clicked()), this, SLOT(selectPicture()));
    picturePath = path;
    picturePreview = preview;

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
        QImage image(name);
        image = image.scaled(100, 100);
        picturePath->clear();
        picturePath->append(name);
        picturePreview->setPixmap(QPixmap::fromImage(image));

    }

}
