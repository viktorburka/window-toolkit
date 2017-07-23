#ifndef APPLICATIONX11_H
#define APPLICATIONX11_H

#include "types.h"
#include "platformapplication.h"

#include <X11/Xlib.h>

#include <map>

namespace Wt {

class Widget;

class ApplicationX11: public PlatformApplication
{
public:
    ApplicationX11();
    ~ApplicationX11();

    void run();

    //static ApplicationX11* instance();

    void addWindow(Widget* widget);

private:
    void leaveEventLoop();
    void processEvent(XEvent* event, Widget* window);

    bool                       m_running;
    std::map<WindowId,Widget*> m_windows;
    //static ApplicationX11*     m_instance;
};

}

#endif
