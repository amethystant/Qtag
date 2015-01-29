#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[]);
void setDarkTheme(QApplication &a);

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
