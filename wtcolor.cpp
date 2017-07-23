#include <X11/Xlib.h>
#include "display-x11.h"

#include "wtcolor.h"

using namespace Wt;

WtColor::WtColor(const std::string & name)
    : r(0x00), g(0x00), b(0x00), a(0x00)
{
    XColor xc, xc2;

    Display* display  = DisplayX11::display;
    Colormap colorMap = DefaultColormap(display, DefaultScreen(display));

    XAllocNamedColor(display, colorMap, name.c_str(), &xc, &xc2);

    r = xc.red; g = xc.green; b = xc.blue;

    m_rgba[0] = r; m_rgba[1] = g; m_rgba[2] = b;
    m_bgra[0] = b; m_bgra[1] = g; m_bgra[2] = r;
}

const char* WtColor::rgba() const
{
    return m_rgba;
}

const char* WtColor::bgra() const
{
    return m_bgra;
}
