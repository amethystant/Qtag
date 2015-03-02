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
