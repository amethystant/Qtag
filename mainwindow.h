#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <QTreeWidgetItem>
#include <QStringList>
#include <QDir>
#include <QResizeEvent>

#include "audiofile.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QList<AudioFile*> listOfFiles;
    void updateViews();
    bool isFileOnList(QString path);

public slots:
    void openFile();
    void openFolder();

};

#endif // MAINWINDOW_H
