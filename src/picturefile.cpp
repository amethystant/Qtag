/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 *
 * (C) 2015 by Karel Patlejch
 *
 * Used libraries:
 *    TagLib - https://github.com/taglib
 *    Qt - http://qt.io
 *
*/

#include "picturefile.h"

PictureFile::PictureFile(const char* path) : TagLib::File(path) {
}

TagLib::ByteVector PictureFile::getData() {
    return readBlock(length());
}

TagLib::Tag* PictureFile::tag() const {
    return 0;
}

TagLib::AudioProperties* PictureFile::audioProperties() const {
    return 0;
}

bool PictureFile::save() {
    return false;
}
