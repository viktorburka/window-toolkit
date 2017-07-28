#include "bindevent.h"
#include "widget.h"

using namespace Wt;

/*!
    \class BindEvent
    \inmodule Wt

    \brief The BindEvent class provides event binding to other objects.

    \ingroup tools

    BindEvent provides binding of event named \a name of widget
    \a widget to invoke a function specified in its \a to method.

    \snippet PushButton btn;
    \snippet BindEvent bind("click", &btn).to([]{printf("Hello!\n")});

    A shorter and more convenient method of binding events looks like this:

    \snippet PushButton btn;
    \snippet btn.bindEvent("click").to([]{printf("Hello!\n")});

    Where \a bindEvent is a method of class \a Widget. In both cases the
    appropriate binding will then be added to the internal list of bindings
    of that particluar widget
*/

/*!
    Constructs BindEvent.
*/
BindEvent::BindEvent(const std::string & name, Widget* widget)
    : m_name(name)
    , m_widget(widget)
{
}

/*!
    Specifies which lambda function to bind the widget event to
*/
void BindEvent::to(std::function<void()> fn)
{
    m_widget->addEventBinding(m_name, fn);
}
