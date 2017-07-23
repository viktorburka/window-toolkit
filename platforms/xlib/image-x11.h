#ifndef IMAGEX11_H
#define IMAGEX11_H

#include "platformimage.h"

#include <X11/Xlib.h>

namespace Wt {

class ImageX11: public PlatformImage
{
public:
    ImageX11(int width, int height, char* data);
    ~ImageX11();

    void* platformImageStruct() const;

private:
    XImage* m_image;
};

}

#endif
