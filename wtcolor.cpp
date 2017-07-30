#include <X11/Xlib.h>
#include "display-x11.h"

#include "wtcolor.h"

using namespace Wt;

/*!
    \class WtColor
    \inmodule Wt

    \brief The WtColor class implements operations with colors.

    \ingroup widgets

    WtColor works with colors and converts them from abstract platform
    independent representation to a platform dependent one. It can operate
    with conventional colors like red, green, blue, etc representing them
    in more complex display system aware colors based on the given palette.

    Using WtColor is easy. Just create it passing a conventional color name
    to its constructor like:

    \code Color red("red");

*/

/*!
    WtColor constructor. Takes conventional color name as parameter.
*/
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

/*!
    Returns RGBA representation of color.
*/
const char* WtColor::rgba() const
{
    return m_rgba;
}

/*!
    Returns BGRA representation of color.
*/
const char* WtColor::bgra() const
{
    return m_bgra;
}
