#ifndef IMAGEPNG_H
#define IMAGEPNG_H

#include "imageformat.h"

namespace Wt {

class ImagePng: public ImageFormat
{
public:
    ImagePng();

    bool readImage(const std::string & filePath);

    char* data() const;
    int width() const;
    int height() const;

    void setRGBAFunc(char* (*func)(char*));

private:
    char*   m_data{nullptr};
    int     m_width{0};
    int     m_height{0};
    char* (*m_rgbaFunc)(char*);
};

}

#endif
