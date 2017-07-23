#ifndef PAINTBRUSH_H
#define PAINTBRUSH_H

#include <string>

namespace Wt {

class Widget;
class Rect;
class WtImage;
class WtColor;
class PlatformPaintBrush;

class PaintBrush
{
public:
    PaintBrush(Widget* widget);

    void drawRect(const Rect & rect);
    void drawRect(int x, int y, int width, int height);
    void fillRect(const Rect & rect);
    void fillRect(int x, int y, int width, int height);
    void setPaintColor(const std::string & colorName);

    void drawText(const std::string & text, const Rect & rect);

    void drawText(const std::string & str, const WtColor & background);
    void drawImage(const WtImage & image, const Rect & rect);

private:
    Widget*             m_surface;
    PlatformPaintBrush* m_platformBrush;
};

}

#endif
