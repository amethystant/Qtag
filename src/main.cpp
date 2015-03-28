#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include "main.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

QString intToString(int i) {

    QString value;
    std::ostringstream convert;
    convert << i;
    value = QString::fromStdString(convert.str());
    return value;

}
