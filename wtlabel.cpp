#include "wtlabel.h"
#include "paintbrush.h"

using namespace Wt;

/*!
    \class WtLabel
    \inmodule Wt

    \brief The WtLabel class draws text label on the screen.

    \ingroup widgets

    WtLabel displays given string as text label on the screen.
*/

/*!
    WtLabel constructor.
*/
WtLabel::WtLabel(Widget* parent)
    : Widget(parent)
{
    setName("WtLabel");
}

/*!
    Returns WtLabel text.
*/
std::string WtLabel::text() const
{
    return m_text;
}

/*!
    Sets WtLabel text.
*/
void WtLabel::setText(const std::string & text)
{
    m_text = text;
    repaint();
}

/*!
    Draws WtLabel widget.
*/
void WtLabel::drawEvent(int x, int y, int width, int height)
{
    PaintBrush pb(this);
    pb.setPaintColor("Black");
    pb.drawText(m_text, Rect(0,0,Widget::width(),Widget::height()));
}
