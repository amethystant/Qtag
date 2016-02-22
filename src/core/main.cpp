/*
 *    Qtag is an advanced but simple to use audio metadata editor. Runs on Linux
 *    and Windows. Supports many formats, including MPEG, Ogg Vorbis, Wave and FLAC
 *
 *    Copyright (C) 2015 - 2016  Karel Patlejch <kaja.patlejch@gmail.com>
 *
 *    Used libraries:
 *      TagLib - http://taglib.github.io/
 *      Qt - http://qt.io
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License along
 *    with this program; if not, write to the Free Software Foundation, Inc.,
 *    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#include "core/mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QStyle>
#include "core/main.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/Qtag.png"));
    QCoreApplication::setApplicationName("Qtag");
    QCoreApplication::setOrganizationName("Qtag");
    QApplication::setStyle(getStyleFromSettings());
    QApplication::setStyle("");
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
        if(s.length() > index)
            s.replace(index, 1, s.at(index).toUpper());
    }
    return s;
}

QStyle* getStyleFromSettings() {

    QSettings settings;
    QVariant value = settings.value("style");
    QString style = value.toString();
    return QStyleFactory::create(style);

}
