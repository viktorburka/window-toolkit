#include "wtlabel.h"
#include "paintbrush.h"

using namespace Wt;

WtLabel::WtLabel(Widget* parent)
    : Widget(parent)
{
    setName("WtLabel");
}

std::string WtLabel::text() const
{
    return m_text;
}

void WtLabel::setText(const std::string & text)
{
    m_text = text;
    repaint();
}

void WtLabel::drawEvent(int x, int y, int width, int height)
{
    PaintBrush pb(this);
    pb.setPaintColor("Black");
    pb.drawText(m_text, Rect(0,0,Widget::width(),Widget::height()));
}
