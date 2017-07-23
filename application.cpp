#include "application.h"
#include "verification.h"
#include "platformapplication.h"

#ifdef GP_X11
#include "application-x11.h"
#endif

#include <stdio.h>
#include <stdlib.h>

using namespace Wt;

Application* Application::m_instance = 0;
PlatformApplication* Application::m_platformApplication = 0;

Application::Application()
{
    if (m_instance) {
        fprintf(stderr, "There can not be more than one instance of Application");
        exit(-1);
    }

#ifdef GP_X11
    m_platformApplication = new ApplicationX11;
#endif
    m_instance = this;
}

Application::~Application()
{
    m_instance = 0;
    delete m_platformApplication;
}

void Application::run()
{
    m_platformApplication->run();
}

void Application::addWindow(Widget* widget)
{
    m_platformApplication->addWindow(widget);
}

Application* Application::instance()
{
    check_null_ptr(m_instance);
    return m_instance;
}

