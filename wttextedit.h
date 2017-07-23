#ifndef WTTEXTEDIT_H
#define WTTEXTEDIT_H

#include "widget.h"

#include <string>

namespace Wt {

class WtTextEdit: public Widget
{
public:
    WtTextEdit(Widget* parent);

    void setText(const std::string & text);

protected:
    void drawEvent(int x, int y, int width, int height);

private:
    std::string m_text;
};

}

#endif
