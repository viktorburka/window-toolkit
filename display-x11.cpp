#include "display-x11.h"
#include "verification.h"

using namespace Wt;

/*!
    \class DisplayX11
    \inmodule Wt

    \brief The DisplayX11 class accumulates X11 backend handlers.

    \ingroup tools

    DisplayX11 is an internal class accumulates the handles that
    X11 system provides such as display, graphics context, font
    info, etc.
*/

Display*        DisplayX11::display     = 0;
GC              DisplayX11::gc          = 0;
Atom            DisplayX11::closeWinMsg = 0;
XFontStruct*    DisplayX11::fontInfo    = 0;

/*!
    Returns current display handler
*/
Display *DisplayX11::currentDisplay()
{
    check_display_x11(display);
    return display;
}

/*!
    Returns current graphics context handler
*/
GC DisplayX11::currentGC()
{
    return gc;
}

/*!
    Returns default font handler
*/
Font DisplayX11::defaultFont()
{
    return fontInfo->fid;
}

/*!
    Adds close window event by getting a notification
    from window manager
*/
void DisplayX11::initWindowManager(Display* display)
{
    closeWinMsg = XInternAtom(display, "WM_DELETE_WINDOW", false);
}
