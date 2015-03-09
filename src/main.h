#ifndef MAIN_H
#define MAIN_H

/*
This file declares some simple non-objected functions and variables
*/

#include <QString>
#include <QApplication>
#include <string>

void setDarkTheme(QApplication &a);
QString intToString(int i);


namespace NamesOfTags {

    const std::string APE = "APE tag";
    const std::string ID3V1= "ID3v1 tag";
    const std::string ID3V2= "ID3v2 tag";
    const std::string ASF= "ASF tag";
    const std::string XIPH= "Xiph Comment";
    const std::string INFO= "RIFF Info tag";

}

#endif // MAIN_H

