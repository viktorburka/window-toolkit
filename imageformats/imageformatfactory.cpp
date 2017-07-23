#include "imageformatfactory.h"
#include "imageformat.h"
#include "image-png.h"

using namespace Wt;

ImageFormat* ImageFormatFactory::create(const std::string & ext)
{
    if (ext == "png")
        return (new ImagePng());
    return nullptr;
}
