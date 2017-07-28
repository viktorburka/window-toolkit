#include "application.h"
#include "verification.h"
#include "platformapplication.h"

#ifdef GP_X11
#include "application-x11.h"
#endif

#include <stdio.h>
#include <stdlib.h>

using namespace Wt;

/*!
    \class Application
    \inmodule Wt

    \brief The Application class represents application abstraction.

    \ingroup tools

    Application implements application abstraction and provides
    such functionality as application event loop processing,
    windows handling and more. It instantiates the platform
    related events processing such as mouse, keyboard, show and
    hide, repaint and other events that the employed window system
    supports.

    There should be only one instance of Application class and it
    needs to be declared before any other class of WT framework
    that uses event processing.
*/

Application* Application::m_instance = 0;
PlatformApplication* Application::m_platformApplication = 0;

/*!
    Constructs an application and instantiates a platform
    dependent event loop processing.
*/
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

/*!
    Application destructor.
*/
Application::~Application()
{
    m_instance = 0;
    delete m_platformApplication;
}

/*!
    Runs application event loop. It starts an internal loop
    that processes all events including mouse, keyboard, show and
    hide, repaint and other events that the employed window system
    supports.

    Warning: It is a blocking call.
*/
void Application::run()
{
    m_platformApplication->run();
}

/*!
    Adds window to the event loop processing. Events
    addressed to the window with this id will be properly
    propagated to the appropriate virtual function calls
    so that the user can handle them
*/
void Application::addWindow(Widget* widget)
{
    m_platformApplication->addWindow(widget);
}

/*!
    Returns application instance. Its a static method
    of a singleton
*/
Application* Application::instance()
{
    check_null_ptr(m_instance);
    return m_instance;
}

