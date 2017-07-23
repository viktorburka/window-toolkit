#include "wttextedit.h"
#include "paintbrush.h"
#include "wtcolor.h"

using namespace Wt;

WtTextEdit::WtTextEdit(Widget* parent)
    : Widget(parent)
{
    setName("WtTextEdit");
}

void WtTextEdit::setText(const std::string & text)
{
    m_text = text;
    repaint();
}

void WtTextEdit::drawEvent(int x, int y, int width, int height)
{
    PaintBrush pb(this);
    WtColor backgroundColor("Light Gray");
    pb.drawText("Hello!", backgroundColor);
}
