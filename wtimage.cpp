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

/*!
    \class WtImage
    \inmodule Wt

    \brief The WtImage class implements operations with image bytes.

    \ingroup widgets

    WtImage is platform and format independent representation of an image
    that allows direct access to its bytes. WtImage can take raster images
    of different formats such as PNG etc and provide a unified API to
    manipulated it. It also integrates to the platoform dependent display
    system allowing to draw given image.

    Loading encoded images with WtImage is as easy as:

    \code WtImage image("picture.png");
*/

/*!
    WtImage constructor. Takes path to image file as parameter.
*/
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

/*!
    WtImage constructor. Takes image size and raw image data
    as parameter.
*/
WtImage::WtImage(int width, int height, char* data)
{
#ifdef GP_X11
    m_platformImage = new ImageX11(width, height, data);
#endif
}
