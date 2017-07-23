#include "window-x11.h"
#include "display-x11.h"
#include "verification.h"
#include "wt.h"

#include <cmath>
#include <X11/Xutil.h>

using namespace Wt;

WindowX11::WindowX11(WindowX11 *parent)
    : m_width(0)
    , m_height(0)
    , m_xpos(0)
    , m_ypos(0)
    , m_topLevel(parent == nullptr)
{
    Display* display = DisplayX11::currentDisplay();

    int screen_num = DefaultScreen(display);
    int border_width = 0;
#ifdef VISUAL_DEBUG
    border_width = 1;
#endif

    m_win = XCreateSimpleWindow(display,
                                m_topLevel ? RootWindow(display, screen_num) : parent->id(),
                                m_xpos, m_ypos,
                                parent->m_width, parent->m_height,
                                border_width, BlackPixel(display, screen_num),
                                WhitePixel(display, screen_num));
    fprintf(stderr, "Created window: %u\n", (uint)m_win);

    if (m_topLevel && !DisplayX11::currentGC())
        DisplayX11::gc = XCreateGC(display, m_win, 0, NULL);

    m_dpix = parent->dpiX();
    m_dpiy = parent->dpiY();

    XSelectInput(display, m_win, ExposureMask | StructureNotifyMask | ButtonPressMask | ButtonReleaseMask);
    XSetWMProtocols(display, m_win, &DisplayX11::closeWinMsg, 1);
}

WindowX11::WindowX11(int width, int height)
    : m_width(width)
    , m_height(height)
    , m_xpos(0)
    , m_ypos(0)
    , m_topLevel(true)
{
    Display* display = DisplayX11::currentDisplay();

    int screen_num = DefaultScreen(display);
    int border_width = 1;

    int widthMM = DisplayWidthMM(display, screen_num);
    int heightMM = DisplayHeightMM(display, screen_num);

    int widthPx = DisplayWidth(display, screen_num);
    int heightPx = DisplayHeight(display, screen_num);

    m_dpix = round(widthPx * 25.4 / widthMM);
    m_dpiy = round(heightPx * 25.4 / heightMM);

    if (m_width == 0 || m_height == 0) {
        ::Window root;
        int x,y;
        uint width, height, border_width, depth;
        XGetGeometry(display, RootWindow(display, screen_num),
                     &root, &x, &y, &width, &height,
                     &border_width, &depth);
        fprintf(stderr, "Warning: Size parameters can't be 0. "
                        "Setting default size to: %d,%d", width, height);
        m_width = width; m_height = height;
    }

    m_win = XCreateSimpleWindow(display,
                                RootWindow(display, screen_num),
                                m_xpos, m_ypos,
                                m_width, m_height,
                                border_width, BlackPixel(display, screen_num),
                                WhitePixel(display, screen_num));
    fprintf(stderr, "Created window: %u\n", (uint)m_win);

    if (!DisplayX11::currentGC()) {
        DisplayX11::gc = XCreateGC(display, m_win, 0, NULL);
        XSetFont(DisplayX11::display, DisplayX11::gc, DisplayX11::fontInfo->fid);
    }

    XSelectInput(display, m_win, ExposureMask | StructureNotifyMask | ButtonPressMask | ButtonReleaseMask);
    XSetWMProtocols(display, m_win, &DisplayX11::closeWinMsg, 1);
}

//WindowX11::WindowX11(int width, int height)
//    : m_width(width)
//    , m_height(height)
//    , m_xpos(0)
//    , m_ypos(0)
//    , m_topLevel(true)
//{
//    Display* display = DisplayX11::currentDisplay();

//    XVisualInfo vinfo;
//    int status = XMatchVisualInfo(display, DefaultScreen(display), 32, TrueColor, &vinfo);
//    WtPrint() << "status:" << status;

//    XSetWindowAttributes attr;
//    attr.colormap = XCreateColormap(display, DefaultRootWindow(display), vinfo.visual, AllocNone);
//WtPrint() << "1";
//    m_win = XCreateWindow(display, DefaultRootWindow(display),
//                          m_xpos, m_ypos,
//                          m_width, m_height,
//                          0,
//                          vinfo.depth,
//                          InputOutput,
//                          vinfo.visual,
//                          CWColormap, &attr);

//    if (!DisplayX11::currentGC()) {
//        DisplayX11::gc = XCreateGC(display, m_win, 0, NULL);
//        XSetFont(DisplayX11::display, DisplayX11::gc, DisplayX11::fontInfo->fid);
//    }
//WtPrint() << "2";
//    XSelectInput(display, m_win, ExposureMask | StructureNotifyMask | ButtonPressMask | ButtonReleaseMask);
//WtPrint() << "3";
//    //XSetWMProtocols(display, m_win, &DisplayX11::closeWinMsg, 1);
//WtPrint() << "4";
//    int widthMM = DisplayWidthMM(display, DefaultScreen(display));
//    int heightMM = DisplayHeightMM(display, DefaultScreen(display));

//    int widthPx = DisplayWidth(display, DefaultScreen(display));
//    int heightPx = DisplayHeight(display, DefaultScreen(display));

//    m_dpix = round(widthPx * 25.4 / widthMM);
//    m_dpiy = round(heightPx * 25.4 / heightMM);
//WtPrint() << "5";
//}

void WindowX11::show()
{
    Display* display = DisplayX11::display;
    XMapWindow(display, m_win);
}

void WindowX11::hide()
{
    Display* display = DisplayX11::display;
    XUnmapWindow(display, m_win);
}

WindowId WindowX11::id() const
{
    return m_win;
}

bool WindowX11::isTopLevel() const
{
    return m_topLevel;
}

void WindowX11::setSize(int width, int height)
{
    Display* display = DisplayX11::currentDisplay();
    m_width = width;
    m_height = height;
    XResizeWindow(display, m_win, m_width, m_height);
}

void WindowX11::setPosition(int x, int y)
{
    Display* display = DisplayX11::currentDisplay();
    XMoveWindow(display, m_win, x, y);
}

int WindowX11::dpiX() const
{
    return m_dpix;
}

int WindowX11::dpiY() const
{
    return m_dpiy;
}

void WindowX11::repaint()
{
    Display* display = DisplayX11::currentDisplay();

    XExposeEvent event;
    event.type = Expose;
    event.display = display;
    event.window = m_win;
    event.x = 0;
    event.y = 0;
    event.width = m_width;
    event.height = m_height;
    event.count = 0;
    //fprintf(stderr, "XSendEvent m_width: %d, m_height: %d\n", m_width, m_height);
    XSendEvent(display, m_win, true, ExposureMask,(XEvent *)&event);
}
