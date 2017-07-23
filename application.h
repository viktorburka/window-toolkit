#ifndef APPLICATION_H
#define APPLICATION_H

#include "platformapplication.h"

namespace Wt {

class Widget;
class PlatformApplication;

class Application
{
public:
    Application();
    virtual ~Application();

    void run();
    void addWindow(Widget* widget);

    static Application* instance();

private:
    static Application* m_instance;
    static PlatformApplication* m_platformApplication;
};

}

#endif
