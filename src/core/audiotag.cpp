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

#include "audiotag.h"
#include "core/audiofile.h"
#include "core/main.h"
#include <QFile>

AudioTag::AudioTag(QObject *parent, TagLib::Tag *tag, TagFormat nameOfTag) :
    QObject(parent) {

    this->tag = tag;
    type = nameOfTag;

}

void AudioTag::setTitle(QString title) {
    tag->setTitle(title.toStdString());
    emit edited();
}

void AudioTag::setTrack(int track) {
    tag->setTrack(track);
    emit edited();
}

void AudioTag::setAlbum(QString album) {
    tag->setAlbum(album.toStdString());
    emit edited();
}

void AudioTag::setArtist(QString artist) {
    tag->setArtist(artist.toStdString());
    emit edited();
}

void AudioTag::setGenre(QString genre) {
    tag->setGenre(genre.toStdString());
    emit edited();
}

void AudioTag::setComment(QString comment) {
    tag->setComment(comment.toStdString());
    emit edited();
}

void AudioTag::setYear(int year) {
    tag->setYear(year);
    emit edited();
}

void AudioTag::setCoverArt(QString picturePath) {

    if(type == TagFormats::ID3V2) {

        TagLib::ID3v2::Tag* id3v2Tag = (TagLib::ID3v2::Tag*) tag;
        if(picturePath.isEmpty()) {
            id3v2Tag->removeFrames("APIC");
            emit edited();
            return;
        }
        TagLib::ID3v2::AttachedPictureFrame* frame = new TagLib::ID3v2::AttachedPictureFrame();
        if(picturePath.endsWith(".jpeg", Qt::CaseInsensitive) ||
                picturePath.endsWith(".jpg", Qt::CaseInsensitive))
            frame->setMimeType("image/jpeg");
        else if(picturePath.endsWith(".png", Qt::CaseInsensitive))
            frame->setMimeType("image/png");
        else
            return;
        QFile f(picturePath);
        if(!f.exists())
            return;
        id3v2Tag->removeFrames("APIC");
        PictureFile picture(picturePath.toStdString().c_str());
        frame->setPicture(picture.getData());
        id3v2Tag->addFrame(frame);

        emit edited();

    } else if(type == TagFormats::APE) {

        TagLib::APE::Tag* apeTag = (TagLib::APE::Tag*) tag;
        if(picturePath.isEmpty()) {
            apeTag->removeItem("COVER ART (FRONT)");
            emit edited();
            return;
        }
        QFile f(picturePath);
        if(!f.exists())
            return;

        apeTag->removeItem("COVER ART (FRONT)");

        PictureFile picture(picturePath.toStdString().c_str());
        TagLib::ByteVector pic = picture.getData();

        TagLib::ByteVector dataToSave("Cover Art (Front).jpg", 22);
        dataToSave.append(pic);

        apeTag->setData("Cover Art (Front)", dataToSave);
        emit edited();

    } else if(type == TagFormats::ASF) {

        TagLib::ASF::Tag* asfTag = (TagLib::ASF::Tag*) tag;
        if(picturePath.isEmpty()) {
            asfTag->removeItem("WM/Picture");
            emit edited();
            return;
        }
        QFile f(picturePath);
        if(!f.exists())
            return;

        PictureFile picture(picturePath.toStdString().c_str());
        TagLib::ByteVector pic = picture.getData();
        TagLib::ASF::Picture asfPic;
        if(picturePath.endsWith(".jpeg", Qt::CaseInsensitive) ||
                picturePath.endsWith(".jpg", Qt::CaseInsensitive))
            asfPic.setMimeType("image/jpeg");
        else if(picturePath.endsWith(".png", Qt::CaseInsensitive))
            asfPic.setMimeType("image/png");
        else
            return;
        asfPic.setPicture(pic);
        asfPic.setType(TagLib::ASF::Picture::FrontCover);
        TagLib::ASF::Attribute attr(asfPic);
        asfTag->removeItem("WM/Picture");
        asfTag->addAttribute("WM/Picture", attr);
        emit edited();

    }

}

QString AudioTag::getTitle() {
    return QString(tag->title().toCString(true));
}

int AudioTag::getTrack() {
    return tag->track();
}

QString AudioTag::getAlbum() {
    return QString(tag->album().toCString(true));
}

QString AudioTag::getArtist() {
    return QString(tag->artist().toCString(true));
}

QString AudioTag::getGenre() {
    return QString(tag->genre().toCString(true));
}

QString AudioTag::getComment() {
    return QString(tag->comment().toCString(true));
}

int AudioTag::getYear() {
    return tag->year();
}

QImage* AudioTag::getCoverArt() {

    if(type == TagFormats::ID3V2) {

        QImage* image = new QImage();
        TagLib::ID3v2::Tag* id3v2Tag = (TagLib::ID3v2::Tag*) tag;
        TagLib::ID3v2::FrameList frameList = id3v2Tag->frameList("APIC");
        if(frameList.isEmpty()) {
            delete image;
            return NULL;
        }
        TagLib::ID3v2::AttachedPictureFrame *pictureFrame =
            static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frameList.front());
        image->loadFromData((const uchar *) pictureFrame->picture().data(), pictureFrame->picture().size());

        return image;

    } else if(type == TagFormats::APE) {

        QImage* image = new QImage();
        TagLib::APE::Tag* apeTag = (TagLib::APE::Tag*) tag;
        TagLib::APE::ItemListMap map = apeTag->itemListMap();
        if(!map.contains("COVER ART (FRONT)")) {
            return NULL;
        }
        TagLib::APE::Item item = map["COVER ART (FRONT)"];
        TagLib::ByteVector byteVector = item.binaryData();

        TagLib::ByteVector stringTerminator('\0');

        int pos = byteVector.find(stringTerminator);
        if(++pos > 0) {
            TagLib::ByteVector pic = byteVector.mid(pos);
            image->loadFromData((const uchar*) pic.data(), pic.size());
            return image;
        }

    } else if(type == TagFormats::ASF) {

        QImage* image = new QImage();
        TagLib::ASF::Tag* asfTag = (TagLib::ASF::Tag*) tag;
        TagLib::ASF::AttributeList attributeList = asfTag->attribute("WM/Picture");
        if(attributeList.size() == 0) {
            return image;
        }
        TagLib::ASF::Attribute attribute = attributeList[0];
        TagLib::ASF::Picture pic = attribute.toPicture();
        TagLib::ByteVector byteVector = pic.picture();
        image->loadFromData((const uchar*) byteVector.data(), byteVector.size());
        return image;

    }

    return NULL;

}

TagFormat AudioTag::getFormat() {
    return type;
}

bool AudioTag::supportsCoverArt() {
    if(type == TagFormats::ID3V2 || type == TagFormats::APE || type == TagFormats::ASF) {
        return true;
    } else {
        return false;
    }
}

bool AudioTag::isEmpty() {
    return tag->isEmpty();
}
