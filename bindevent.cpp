#include "bindevent.h"
#include "widget.h"

using namespace Wt;

BindEvent::BindEvent(const std::string & name, Widget* widget)
    : m_name(name)
    , m_widget(widget)
{
}

void BindEvent::to(std::function<void()> fn)
{
    m_widget->addEventBinding(m_name, fn);
}
