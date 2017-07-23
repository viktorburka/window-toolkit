#include "image-x11.h"
#include "display-x11.h"

using namespace Wt;

ImageX11::ImageX11(int width, int height, char* data)
{
    Display* display = DisplayX11::currentDisplay();
    Visual*   visual = DefaultVisual(display, DefaultScreen(display));
    int        depth = DefaultDepth(display, DefaultScreen(display));

    m_image = XCreateImage(display, visual, depth, ZPixmap, 0, data,
                           width, height, 32, 0);
}

ImageX11::~ImageX11()
{
    //XDestroyImage(m_image);
}

void* ImageX11::platformImageStruct() const
{
    return (void*)m_image;
}
