#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include "main.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QStringList files = a.arguments();
    files.removeFirst();
    MainWindow window(files);
    window.show();

    return a.exec();
}

QString intToString(int i) {

    QString value;
    std::ostringstream convert;
    convert << i;
    value = QString::fromStdString(convert.str());
    return value;

}

QString capitalized(QString s) {
    s.replace(0, 1, s.at(0).toUpper());
    int index = 0;
    for(int i = 0; i < s.count(' '); i++) {
        index = s.indexOf(' ', index) + 1;
        s.replace(index, 1, s.at(index).toUpper());
    }
    return s;
}
