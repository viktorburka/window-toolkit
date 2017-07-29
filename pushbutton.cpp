#include "pushbutton.h"
#include "paintbrush.h"
#include "wt.h"

using namespace Wt;

/*!
    \class PushButton
    \inmodule Wt

    \brief The PushButton class implements push button widget.

    \ingroup widgets

    PushButton servers a general user interface element that
    issues events when its clicked. It can contain text
    that explains the purpose of the button. When the button
    is clicked a\ click event will be emitted.
*/

/*!
    PushButton contructor.
*/
PushButton::PushButton(Widget* parent)
    : Widget(parent)
    , m_pressed(false)
{
    setName("PushButton");
}

/*!
    PushButton drawing procecure.
*/
void PushButton::drawEvent(int x, int y, int width, int height)
{
    PaintBrush pb(this);

    pb.setPaintColor(m_pressed ? "Web Gray" : "Dark Gray");
    pb.fillRect(0, 0, Widget::width(), Widget::height());

    pb.setPaintColor("Black");
    pb.drawRect(0, 0, Widget::width()-1, Widget::height()-1);

    if (m_text.length())
        pb.drawText(m_text, Rect(0,0,Widget::width(),Widget::height()));
}

/*!
    Returns text string assigned to a button.
*/
std::string PushButton::text() const
{
    return m_text;
}

/*!
    Assignes text string display inside the button.
*/
void PushButton::setText(const std::string & text)
{
    m_text = text;
    repaint();
}

/*!
    Mouse press handler.
*/
void PushButton::mousePressEvent(int x, int y, MouseButtons state)
{
    m_pressed = state && LeftButton;
    repaint();
}

/*!
    Mouse release handler. Issues \a click signal
*/
void PushButton::mouseReleaseEvent(int x, int y, MouseButtons state)
{
    m_pressed = !(state && LeftButton);
    repaint();
    sendEvent("click");
}
