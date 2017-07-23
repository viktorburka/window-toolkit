#ifndef BINDEVENT_H
#define BINDEVENT_H

#include <string>
#include <functional>

namespace Wt {

class Widget;

class BindEvent
{
public:
    BindEvent(const std::string& name, Widget* widget);
    void to(std::function<void()> fn);

private:
    std::string m_name;
    Widget* m_widget{nullptr};
};

}

#endif
