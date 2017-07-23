#ifndef IMAGEFORMATFACTORY_H
#define IMAGEFORMATFACTORY_H

#include <string>

namespace Wt {

class ImageFormat;

class ImageFormatFactory
{
public:
    static ImageFormat* create(const std::string & ext);
};

}

#endif
