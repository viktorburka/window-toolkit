#ifndef IMAGEFORMAT_H
#define IMAGEFORMAT_H

#include <string>

namespace Wt {

class ImageFormat
{
public:
    virtual ~ImageFormat() {}

    virtual bool readImage(const std::string & filePath) = 0;

    virtual char* data() const = 0;
    virtual int width() const = 0;
    virtual int height() const = 0;

    virtual void setRGBAFunc(char* (*func)(char*)) = 0;
};

}

#endif
