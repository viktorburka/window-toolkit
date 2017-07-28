#include "listview.h"
#include "paintbrush.h"
#include "rect.h"
#include "wt.h"

#include <cmath>

using namespace Wt;

/*!
    \class ListView
    \inmodule Wt

    \brief The ListView class represent scrollable list view widget.

    \ingroup widgets

    ListView widget displays a scrollable list of elements. If the
    number of items by their height exceed ListView area, appropriate
    scroll bar will be automatically added by the widget.

    To add elements to ListView call \a setData function with a list
    of strings to be displayed in each item of ListView.

    To highlight an element in ListView call \a setSelectedIndex method
    passing the index of desired element starting from 0.
*/

const int ItemHeight     = 30;
const int ScrollBarWidth = 20;
const int ThumbLength    = ScrollBarWidth - 4; // minux 2px on each side

/*!
    Constructs ListView widget taking \a parent widget as its container.
*/
ListView::ListView(Widget * parent)
    : Widget(parent)
    , m_index(-1)
{
}

/*!
    Sets a list of strings to be displayed in each item of ListView.

    If ListView already contains data, it will be overwritten with
    the new data.
*/
void ListView::setData(const std::list<std::string> & items)
{
    m_items = items;
    repaint();
}

/*!
    Returns highlighted item of ListView.
*/
int ListView::selectedIndex() const
{
    return m_index;
}

/*!
    Highlights ListView item by \a index starting from 0.
*/
void ListView::setSelectedIndex(int index)
{
    m_index = index;
    repaint();
}

/*!
    Draws the ListView widget on the screen by its coordinates.
*/
void ListView::drawEvent(int x, int y, int width, int height)
{
    PaintBrush pb(this);

    int ycoord = 0;
    int effective_width = this->width();

    // draw scroll bar
    if (ItemHeight*m_items.size() > this->height()) {
        effective_width = this->width() - ScrollBarWidth;
        drawScrollBarFrame(pb, m_sg);
        drawThumb(pb, m_sg.thumbUpRect(), true);
        drawThumb(pb, m_sg.thumbDownRect(), false);
        drawScroller(pb, m_sg.scrollerAreaRect());
    }

    int i = 0;
    for(auto it = m_items.begin(); it != m_items.end(); ++it, ++i) {
        Rect itemRect(0, ycoord-m_viewOffset, effective_width, ItemHeight+1);
        pb.setPaintColor(i == m_index ? "Light Sky Blue" : "White");
        pb.fillRect(itemRect);
        pb.setPaintColor("Black");
        pb.drawRect(itemRect);
        pb.setPaintColor("Black");
        pb.drawText(*it, itemRect);
        ycoord += ItemHeight;
    }
}

/*!
    Mouse press event handler. Highlights ListView item if left button
    is clicked.
*/
void ListView::mousePressEvent(int x, int y, MouseButtons state)
{
    if (state && LeftButton) {
        if (m_viewRect.contains(x,y)) {
            int index = y / ItemHeight;
            setSelectedIndex(index);
        } else if (m_sg.thumbUpRect().contains(x,y)) {
            m_viewOffset = Wt::boundary(m_viewOffset - ItemHeight/2, 0, m_maxViewOffset);
            int scrollerHeight = m_sg.scrollerHeight(ItemHeight, m_items.size());
            m_scrollerOffset = (m_sg.scrollerAreaRect().height() - scrollerHeight) * m_viewOffset/m_maxViewOffset;
            repaint();
        } else if (m_sg.thumbDownRect().contains(x,y)) {
            m_viewOffset = Wt::boundary(m_viewOffset + ItemHeight/2, 0, m_maxViewOffset);
            int scrollerHeight = m_sg.scrollerHeight(ItemHeight, m_items.size());
            m_scrollerOffset = (m_sg.scrollerAreaRect().height() - scrollerHeight) * m_viewOffset/m_maxViewOffset;
            repaint();
        }
    }
}

/*!
    Mouse release event handler. By releasing the mouse button
    the widget sends \a selectedItemChanged event notifying that
    an item has been selected.
*/
void ListView::mouseReleaseEvent(int x, int y, MouseButtons state)
{
    if (m_index != -1)
        sendEvent("selectedItemChanged");
}

/*!
    Geometry change event handler. Causes the widget content to be
    properly redrawn based on the new widget geometry
*/
void ListView::geometryChangeEvent(int x, int y, int width, int height)
{
    int viewWidth = width - ScrollBarWidth;
    int offset    = m_sg.borderOffset();

    Rect scrolBarRect     = Rect(viewWidth-1, 0, ScrollBarWidth, height); // -1 to allign it with list view right border
    Rect thumbUpRect      = Rect(scrolBarRect.x()+offset, offset, ThumbLength, ThumbLength);
    Rect thumbDownRect    = Rect(scrolBarRect.x()+offset, height-ThumbLength-offset, ThumbLength, ThumbLength);
    Rect scrollerAreaRect = Rect(scrolBarRect.x()+offset, ThumbLength+offset+1, ThumbLength, height-(ThumbLength+offset+1)*2);

    m_sg.setRect(scrolBarRect);
    m_sg.setThumbUpRect(thumbUpRect);
    m_sg.setThumbDownRect(thumbDownRect);
    m_sg.setScrollerAreaRect(scrollerAreaRect);

    m_viewRect = Rect(0, 0, viewWidth, height);

    int totalHeight = m_items.size()*ItemHeight;
    m_maxViewOffset    = totalHeight <= height ? 0 : (totalHeight - height);
}

/*!
    Draws ListView scroll bar frame
*/
void ListView::drawScrollBarFrame(PaintBrush & pb, const Rect & rect) const
{
    pb.setPaintColor("Light Steel Blue");
    pb.fillRect(rect);
    pb.setPaintColor("Black");
    pb.drawRect(rect);
}

/*!
    Draws ListView scroll bar thumb element which is a clickable area on
    scroll bar to scroll ListView up and down
*/
void ListView::drawThumb(PaintBrush & pb, const Rect & rect, bool up) const
{
    pb.setPaintColor("Steel Blue");
    pb.fillRect(rect);
    pb.setPaintColor("Black");
    pb.drawRect(rect);
}

/*!
    Draws ListView scroll bar scroller indicating the relative position
    of ListView content being scrolled
*/
void ListView::drawScroller(PaintBrush & pb, const Rect & rect) const
{
    int scrollerHeight = m_sg.scrollerHeight(ItemHeight, m_items.size());
    Rect scrollerRect(rect.x(), rect.y()+m_scrollerOffset,
                      rect.width(), scrollerHeight);

    pb.setPaintColor("Powder Blue");
    pb.fillRect(scrollerRect);
    pb.setPaintColor("Black");
    pb.drawRect(scrollerRect);
}
