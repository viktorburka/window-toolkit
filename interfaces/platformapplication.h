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
    //virtual void setInstance(Application* app) = 0;

    //static Application* instance();

    virtual void addWindow(Widget* widget) {}

//private:
//    static Application* m_instance;
};

}

#endif
