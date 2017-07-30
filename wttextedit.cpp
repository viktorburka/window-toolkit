#include "wttextedit.h"
#include "paintbrush.h"
#include "wtcolor.h"

using namespace Wt;

/*!
    \class WtTextEdit
    \inmodule Wt

    \brief The WtTextEdit class implements multiline text edit widget.

    \ingroup widgets

    WtTextEdit widget is a multiline text editor.
*/

/*!
    WtTextEdit constructor.
*/
WtTextEdit::WtTextEdit(Widget* parent)
    : Widget(parent)
{
    setName("WtTextEdit");
}

/*!
    Sets WtTextEdit text.
*/
void WtTextEdit::setText(const std::string & text)
{
    m_text = text;
    repaint();
}

/*!
    Draws WtTextEdit.
*/
void WtTextEdit::drawEvent(int x, int y, int width, int height)
{
    PaintBrush pb(this);
    WtColor backgroundColor("Light Gray");
    pb.drawText("Hello!", backgroundColor);
}
