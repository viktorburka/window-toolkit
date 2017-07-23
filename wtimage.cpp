#include "wtimage.h"
#include "imageformat.h"
#include "imageformatfactory.h"
#include "wt.h"

#ifdef GP_X11
#include "image-x11.h"
#endif

char* x11rgba(char* rgba) {
    char r = rgba[0];
    char g = rgba[1];
    char b = rgba[2];
    char a = rgba[3];
    rgba[0] = b;
    rgba[1] = g;
    rgba[2] = r;
    rgba[3] = a;
    return rgba;
}

using namespace Wt;

WtImage::WtImage(const std::string & filePath)
{
    using std::string;
    const string png = "png";
    char* data = nullptr;

    string::size_type pos = filePath.rfind('.');
    if (pos != string::npos) {
        string ext = filePath.substr(pos+1, png.size());
        if (ext == png) {
            ImageFormat* image = ImageFormatFactory::create(ext);
#ifdef GP_X11
            image->setRGBAFunc(x11rgba);
#endif
            if (image->readImage(filePath)) {
                data = image->data();
                m_width = image->width();
                m_height = image->height();
            }
        }
    }

    if (data == nullptr || m_width == 0 || m_height == 0) {
        WtPrint() << "Error loading image";
    }
#ifdef GP_X11
    m_platformImage = new ImageX11(m_width, m_height, data);
#endif
}

WtImage::WtImage(int width, int height, char* data)
{
#ifdef GP_X11
    m_platformImage = new ImageX11(width, height, data);
#endif
}
