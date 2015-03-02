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
