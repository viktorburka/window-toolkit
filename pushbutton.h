#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include "widget.h"

#include <string>

namespace Wt {

class PushButton: public Widget
{
public:
    PushButton(Widget* parent);

    std::string text() const;
    void setText(const std::string & text);

protected:
    void drawEvent(int x, int y, int width, int height);
    void mousePressEvent(int x, int y, MouseButtons state);
    void mouseReleaseEvent(int x, int y, MouseButtons state);

private:
    bool m_pressed;
    std::string m_text;
};

}

#endif
