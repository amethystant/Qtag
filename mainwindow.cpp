#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
    ui->treeWidget->setColumnCount(1);

    QObject::connect(ui->actionOpenFile, SIGNAL(triggered()), this, SLOT(openFile()));
    QObject::connect(ui->actionOpenFolder, SIGNAL(triggered()), this, SLOT(openFolder()));

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openFile() {

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setOption(QFileDialog::DontUseNativeDialog);
#ifdef WIN32
    dialog.setDirectory("C:/");
#else
    dialog.setDirectory("/home");
#endif
    dialog.setNameFilter(
                tr("Audio files (*.mp3 *.mp4 *.wav *.wave *.flac *.ogg *.wma *.asf *.wv)"));
    dialog.setViewMode(QFileDialog::Detail);
    dialog.show();
    if(dialog.exec()) {

        QStringList selectedFiles = dialog.selectedFiles();
        int numOfFiles = selectedFiles.length();
        int i;
        for(i = 0; i < numOfFiles; i++) {

            QString path = selectedFiles.value(i);
            if(!isFileOnList(path)) {
                AudioFile *newFile = new AudioFile(path, this);
                listOfFiles.append(newFile);
            }

        }

    }

    updateViews();

}

typedef struct {
    QList<AudioFile*> listOfFiles;
    QString name;
} Album;

typedef struct {
    QList<Album> listOfAlbums;
    QString name;
} Artist;

void MainWindow::updateViews() {

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(listOfFiles.length());
    ui->tableWidget->setSortingEnabled(false);

    int i;
    for(i = 0; i < listOfFiles.length(); i++) {

        AudioFile *f = listOfFiles.at(i);
        QTableWidgetItem *item_path = new QTableWidgetItem(f->getPath().split("/").last());
        QTableWidgetItem *item_name = new QTableWidgetItem(f->getName());
        QTableWidgetItem *item_artist = new QTableWidgetItem(f->getArtist());
        ui->tableWidget->setItem(i, 0, item_path);
        ui->tableWidget->setItem(i, 1, item_name);
        ui->tableWidget->setItem(i, 2, item_artist);
    }

    ui->treeWidget->clear();
    QList<Artist> listOfArtists;
    for(i = 0; i < listOfFiles.length(); i++) {

        AudioFile *f = listOfFiles.at(i);
        int i1 = 0;
        bool isArtistOnList = false;
        while(i1 < listOfArtists.length() && !isArtistOnList) {
            if(listOfArtists.at(i1).name.compare(f->getArtist()) == 0) {
                isArtistOnList = true;
            } else {
                i1++;
            }
        }
        if(!isArtistOnList) {

            Artist newArtist;
            newArtist.name = f->getArtist();
            QList<Album> newAlbumList;
            Album newAlbum;
            newAlbum.name = f->getAlbum();
            newAlbum.listOfFiles.append(f);
            newAlbumList.append(newAlbum);
            newArtist.listOfAlbums.append(newAlbumList);
            listOfArtists.append(newArtist);

        } else {

            int index = i1;
            Artist artist = listOfArtists.at(index);
            i1 = 0;
            bool isAlbumOnList = false;
            while(i1 < artist.listOfAlbums.length() && !isAlbumOnList) {
                if(artist.listOfAlbums.at(i1).name.compare(f->getAlbum()) == 0) {
                    isAlbumOnList = true;
                } else {
                    i1++;
                }
            }

            if(!isAlbumOnList) {
                Album newAlbum;
                newAlbum.name = f->getAlbum();
                newAlbum.listOfFiles.append(f);
                artist.listOfAlbums.append(newAlbum);
            } else {
                int index1 = i1;
                Album al = artist.listOfAlbums.at(index);
                al.listOfFiles.append(f);
                artist.listOfAlbums.replace(index1, al);
            }

            listOfArtists.replace(index, artist);
        }

    }

    for(i = 0; i < listOfArtists.length(); i++) {

        QTreeWidgetItem *artistItem = new QTreeWidgetItem();
        Artist artist = listOfArtists.at(i);
        artistItem->setText(0, artist.name);

        int i1;
        for(i1 = 0; i1 < artist.listOfAlbums.length(); i1++) {
            Album album = artist.listOfAlbums.at(i1);
            QTreeWidgetItem *albumItem = new QTreeWidgetItem();
            albumItem->setText(0, album.name);

            int i2;
            for(i2 = 0; i2 < album.listOfFiles.length(); i2++) {

                AudioFile *f = album.listOfFiles.at(i2);
                QTreeWidgetItem *fileItem = new QTreeWidgetItem();
                fileItem->setText(0, f->getName());

                albumItem->addChild(fileItem);
            }

            artistItem->addChild(albumItem);
        }

        ui->treeWidget->addTopLevelItem(artistItem);
    }
}


void MainWindow::openFolder() {

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    dialog.setOption(QFileDialog::DontUseNativeDialog);
#ifdef WIN32
    dialog.setDirectory("C:/");
#else
    dialog.setDirectory("/home");
#endif
    dialog.setViewMode(QFileDialog::Detail);
    dialog.show();
    if(dialog.exec()) {

        QDir dir(dialog.selectedFiles().at(0));
        QStringList listOfContent = dir.entryList(QDir::Files);
        int i;
        for(i = 0; i < listOfContent.length(); i++) {
            QString s = dir.absoluteFilePath(listOfContent.at(i));
            if((s.endsWith(".mp3", Qt::CaseInsensitive) ||
                          s.endsWith(".flac", Qt::CaseInsensitive) ||
                          s.endsWith(".wav", Qt::CaseInsensitive) ||
                          s.endsWith(".mp4", Qt::CaseInsensitive) ||
                          s.endsWith(".wv", Qt::CaseInsensitive) ||
                          s.endsWith(".ogg", Qt::CaseInsensitive) ||
                          s.endsWith(".wma", Qt::CaseInsensitive) ||
                          s.endsWith(".asf", Qt::CaseInsensitive) ||
                          s.endsWith(".wave", Qt::CaseInsensitive) ) && !isFileOnList(s)) {
                AudioFile *newFile = new AudioFile(s);
                listOfFiles.append(newFile);
            }
        }

    }

    updateViews();

}

bool MainWindow::isFileOnList(QString path) {
    int i = 0;
    while(i < listOfFiles.length()) {
        if(path.compare(listOfFiles.at(i)->getPath()) == 0)
            return true;
        i++;
    }

    return false;
}
