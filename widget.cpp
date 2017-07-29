#include "widget.h"
#include "application.h"
#include "verification.h"
#include "paintbrush.h"

#ifdef GP_X11
#include "window-x11.h"
#endif

#include <algorithm>

using namespace Wt;

/*!
    \class Widget
    \inmodule Wt

    \brief The Widget class is a base class for any visual elment of Window Toolkit.

    \ingroup widgets

    Widget implements all the base wirting with the platform drawing functions to
    allow display visual elements. It is a base class of Window Toolkit for visual
    elements. It provides support for user events as well as drawing through overriding
    its virtual functions such as \a drawEvent, \a mousePressEvent,
    \a mouseReleaseEvent etc. For example this drawing function will draw a red rectangle:

    \code void RectDrawingWidget::drawEvent(int x, int y, int width, int height) {
    \code   PaintBrush painter(this);
    \code   painter.setPaintColor("red");
    \code   painter.drawRect(0,0,20,20);
    \code }

    A widget can have a parent widget which would be in this case its container. Which
    means it will fit the parent geometry as well as resemble some of the parent properties
    shuch as visible, enable, etc. This means once the parent of the widget is hidden,
    the widget will be hidden as well. The widget's parent can be set to NULL. In this
    case the widget becomes top level window.

    In Window Toolkit a Widget is also a base class for events operation. You can bind an
    event and send an event using its API through \a bindEvent and \a sendEvent functions.

    Widget carries such geometry properties as \a x, \a y, \a width and \a height which
    can be set through \a setSize and \a setPosition methods.
*/

/*!
    Widget constructor. Takes parameter \parent as its parent widget. If NULL passed
    as a parent, the widget will be displayed as top level window.
*/
Widget::Widget(Widget* parent)
    : m_x(0), m_y(0)
    , m_width(0), m_height(0)
    , m_visible(false)
    , m_parent(parent)
    , m_name("Widget")
{
#ifdef GP_X11
    WindowX11* x11win = dynamic_cast<WindowX11*>(parent->m_platformWin.get());
    check_null_ptr(x11win);
    m_platformWin.reset(new WindowX11(x11win));
#endif
    Application::instance()->addWindow(this);

    parent->m_children.push_back(this);

    if (parent->isVisible())
        show();
}

/*!
    Widget constructor with \a width and \a height parameters.
*/
Widget::Widget(int width, int height)
    : m_x(0), m_y(0)
    , m_width(width), m_height(height)
    , m_visible(false)
    , m_parent(0)
    , m_name("Widget")
{
#ifdef GP_X11
    m_platformWin.reset(new WindowX11(width, height));
#endif
    Application::instance()->addWindow(this);
}

/*!
    Marks widget to be shown on the screen once event loop processes visibility event.

    Note: It doesn't immediatelly show the widget. The widget will be shown on the screen
    only after the event loop processes the visibility event which requires event loop
    to be working and processing events.
*/
void Widget::show()
{
    m_platformWin->show();
    for(Widget* widget: m_children)
        widget->show();
}

/*!
    Marks widget to be hidden once event loop processes visibility event.

    Note: It doesn't immediatelly hide the widget. The widget will be hidden
    only after the event loop processes the visibility event which requires event loop
    to be working and processing events.
*/
void Widget::hide()
{
    m_platformWin->hide();
}

/*!
    Returns platform dependent window id.
*/
WindowId Widget::id() const
{
    return m_platformWin->id();
}

/*!
    Returns whether widget is high level.
*/
bool Widget::isTopLevel() const
{
    return m_platformWin->isTopLevel();
}

/*!
    Returns whether widget is visible.
*/
bool Widget::isVisible() const
{
    return m_visible;
}

/*!
    Returns widget's width.
*/
int Widget::width() const
{
    return m_width;
}

/*!
    Returns widget's height.
*/
int Widget::height() const
{
    return m_height;
}

/*!
    Returns widget's x coordinate (top left corner) in its parent coordiante system.
    If not parent is set, returns is coordinate in the desktop/screen coordinates.
*/
int Widget::x() const
{
    return m_x;
}

/*!
    Returns widget's y coordinate (top left corner) in its parent coordiante system.
    If not parent is set, returns is coordinate in the desktop/screen coordinates.
*/
int Widget::y() const
{
    return m_y;
}

/*!
    Returns widget's surface DPI on x scale.
*/
int Widget::dpiX() const
{
    return m_platformWin->dpiX();
}

/*!
    Returns widget's surface DPI on y scale.
*/
int Widget::dpiY() const
{
    return m_platformWin->dpiY();
}

/*!
    Sets widget size.
*/
void Widget::setSize(int width, int height)
{
    m_platformWin->setSize(width, height);
    m_width = width;
    m_height = height;
}

/*!
    Sets widget position.
*/
void Widget::setPosition(int x, int y)
{
    m_platformWin->setPosition(x, y);
    m_x = x;
    m_y = y;
}

/*!
    Returns widget name.
*/
std::string Widget::name() const
{
    return m_name;
}

/*!
    Sets widget name.
*/
void Widget::setName(const std::string & name)
{
    m_name = name;
}

/*!
    Registers BindEvent object to bound to a function specified in its \a to
    method.
*/
BindEvent Widget::bindEvent(const std::string & name)
{
    auto it = std::find(m_events.begin(), m_events.end(), name);
    if (it != m_events.end()) {
        m_events.push_back(name);
    }
    return BindEvent(name, this);
}

/*!
    Registers event with name \a name to invoke function \a fn.
*/
void Widget::addEventBinding(const std::string & name, std::function<void()> fn)
{
    m_bindings[name] = fn;
}

/*!
    Sends event with name \a name. This event needs be bound in advance to have
    any effect.
*/
void Widget::sendEvent(const std::string & name)
{
    auto it = m_bindings.find(name);
    if (it != m_bindings.end()) {
        m_bindings[name]();
    }
}

/*!
    Schedules widget repant. Repaint will call \a drawEvent once it has been
    processed by the event loop.
*/
void Widget::repaint()
{
    m_platformWin->repaint();
}

/*!
    Widget background drawing method which fills the widget background before any
    \a drawEvent function is called.
*/
void Widget::drawBackground(int x, int y, int width, int height)
{
    PaintBrush pb(this);
    pb.setPaintColor("LightGrey");
    pb.fillRect(x, y, width, height);
}
