#ifndef MAIN_H
#define MAIN_H

/*
This file declares some simple non-objected functions and variables
*/

#include <QString>
#include <QApplication>
#include <QStyle>
#include <QSettings>
#include <QVariant>
#include <string>

QString intToString(int i);
QString capitalized(QString s);


const std::string NAME_FILTER = "Audio files (*.mp3 *.wav *.wave *.flac *.ogg *.wma *.asf *.wv)";

namespace NamesOfTags {

    const std::string APE = "APE tag";
    const std::string ID3V1= "ID3v1 tag";
    const std::string ID3V2= "ID3v2 tag";
    const std::string ASF= "ASF tag";
    const std::string XIPH= "Xiph Comment";
    const std::string INFO= "RIFF Info tag";

}

QStyle* getStyleFromSettings();

#endif // MAIN_H

