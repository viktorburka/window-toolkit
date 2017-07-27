#ifndef PLATFORMAPPLICATION_H
#define PLATFORMAPPLICATION_H

namespace Wt {

class Widget;

class PlatformApplication
{
public:
    PlatformApplication() {}
    virtual ~PlatformApplication() {}

    virtual void run() = 0;

    virtual void addWindow(Widget* widget) {}
};

}

#endif
