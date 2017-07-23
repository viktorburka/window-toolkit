#ifndef WTIMAGE_H
#define WTIMAGE_H

#include <string>

namespace Wt {

class PlatformImage;

class WtImage
{
public:
    WtImage(const std::string & filePath);
    WtImage(int width, int height, char* data);

    inline int width() const
        { return m_width; }
    inline int height() const
        { return m_height; }

private:
    PlatformImage* m_platformImage;
#ifdef GP_X11
    friend class PaintBrushX11;
#endif
    int m_width  = 0;
    int m_height = 0;

};

}

#endif
