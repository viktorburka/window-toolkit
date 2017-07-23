#ifndef PLATFORMPAINTBRUSH_H
#define PLATFORMPAINTBRUSH_H

#include <string>

namespace Wt {

class Rect;
class WtImage;

class PlatformPaintBrush
{
public:
    virtual ~PlatformPaintBrush() {}

    virtual void drawRect(int x, int y, int width, int height) = 0;
    virtual void fillRect(int x, int y, int width, int height) = 0;

    virtual void setPaintColor(const std::string & colorName) = 0;

    virtual void drawText(const std::string & text) = 0;
    virtual void drawText(const std::string & text, const Rect & rect) = 0;

    virtual void drawImage(const WtImage & image, const Rect & rect) = 0;
};

}

#endif
