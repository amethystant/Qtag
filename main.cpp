#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include "main.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    setDarkTheme(a);
    MainWindow w;
    w.show();

    return a.exec();
}

void setDarkTheme(QApplication &a) {

    QFile f(":qdarkstyle/style.qss");
    if (f.exists()) {

        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        a.setStyleSheet(ts.readAll());
    }

}


QString intToString(int i) {

    QString value;
    std::ostringstream convert;
    convert << i;
    value = QString::fromStdString(convert.str());
    return value;

}
