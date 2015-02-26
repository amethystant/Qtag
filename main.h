#ifndef MAIN_H
#define MAIN_H

/*
This file declares some simple non-objected functions and variables
*/

#include <QString>
#include <QApplication>
#include <string>

const std::string NO_PICTURE = "(No cover picture is included)"; //this string is used in the cover preview if no cover is available

void setDarkTheme(QApplication &a);
QString intToString(int i);

#endif // MAIN_H

