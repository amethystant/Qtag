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

#ifndef PICTUREFILE_H
#define PICTUREFILE_H

#include <taglib.h>
#include <tfile.h>

class PictureFile : public TagLib::File {

public:
    PictureFile(const char* path);
    TagLib::ByteVector getData();

private:
    virtual TagLib::Tag *tag() const;
    virtual TagLib::AudioProperties *audioProperties() const;
    virtual bool save();

};

#endif // PICTUREFILE_H
