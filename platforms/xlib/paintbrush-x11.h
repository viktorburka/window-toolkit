#ifndef PAINTBRUSHX11_H
#define PAINTBRUSHX11_H

#include "platformpaintbrush.h"

namespace Wt {

class WindowX11;
class Rect;

class PaintBrushX11: public PlatformPaintBrush
{
public:
    PaintBrushX11(WindowX11* surface);

    void drawRect(int x, int y, int width, int height);
    void fillRect(int x, int y, int width, int height);

    void setPaintColor(const std::string & colorName);

    void drawText(const std::string & text);
    void drawText(const std::string & text, const Rect & rect);

    void drawImage(const WtImage & image, const Rect & rect);

private:
    WindowX11* m_surface;
};

}

#endif
