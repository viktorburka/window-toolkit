#include "paintbrush-x11.h"
#include "display-x11.h"
#include "window-x11.h"
#include "rect.h"
#include "platformimage.h"
#include "wtimage.h"

using namespace Wt;

PaintBrushX11::PaintBrushX11(WindowX11* surface)
    : m_surface(surface)
{
    Display* display = DisplayX11::display;
    GC gc = DisplayX11::currentGC();
    XSetFillStyle(display, gc, FillSolid);
}

void PaintBrushX11::drawRect(int x, int y, int width, int height)
{
    Display* display = DisplayX11::display;
    GC gc = DisplayX11::currentGC();
    XDrawRectangle(display, m_surface->id(), gc, x, y, width-1, height-1);
}

void PaintBrushX11::fillRect(int x, int y, int width, int height)
{
    Display* display = DisplayX11::display;
    GC gc = DisplayX11::currentGC();
    XFillRectangle(display, m_surface->id(), gc, x, y, width, height);
}

void PaintBrushX11::setPaintColor(const std::string & colorName)
{
    Colormap colorMap;
    XColor xc, xc2;

    Display* display = DisplayX11::display;
    GC gc = DisplayX11::currentGC();
    colorMap = DefaultColormap(display, DefaultScreen(display));

    XAllocNamedColor(display, colorMap, colorName.c_str(), &xc, &xc2);
    XSetForeground(display, gc, xc.pixel);
}

void PaintBrushX11::drawText(const std::string & text)
{
//    Display* display = DisplayX11::display;
//    GC gc = DisplayX11::currentGC();
//    XFontStruct* fontInfo = DisplayX11::fontInfo;

//    auto textWidth = XTextWidth(fontInfo, text.data(), text.length());

//    XDrawString(display, m_surface->id(), gc,
//                (m_surface->width()-textWidth)/2,
//                (m_surface->height() + fontInfo->ascent)/2,
//                text.data(), text.length());
}

void PaintBrushX11::drawText(const std::string & text, const Rect & rect)
{
    Display* display = DisplayX11::display;
    GC gc = DisplayX11::currentGC();
    XFontStruct* fontInfo = DisplayX11::fontInfo;

    auto textWidth = XTextWidth(fontInfo, text.data(), text.length());

    XDrawString(display, m_surface->id(), gc,
                (rect.geometry(Rect::w)-textWidth)/2,
                (rect.geometry(Rect::h)+fontInfo->ascent)/2 + rect.y(),
                text.data(), text.length());
}

void PaintBrushX11::drawImage(const WtImage & image, const Rect & rect)
{
    Display* display = DisplayX11::display;
    GC gc = DisplayX11::currentGC();
    XImage* img = (XImage*)image.m_platformImage->platformImageStruct();

    XPutImage(display, m_surface->id(), gc, img,
              0, 0,
              rect.x(), rect.y(),
              img->width, img->height);
}
