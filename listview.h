#ifndef LISTVIEW_H
#define LISTVIEW_H

#include "widget.h"
#include "rect.h"
#include "wt.h"

#include <string>
#include <list>

namespace Wt {

class PaintBrush;

class ScrollBarGeometry: public Rect
{
public:
    ScrollBarGeometry() {}
    ScrollBarGeometry(int x, int y, int width, int height)
        : Rect(x, y, width, height) {}

    int scrollerOffset() const
        { return m_offset; }
    void setScrollerOffset(int offset)
        { m_offset = offset; }

    Rect scrollerAreaRect() const
        { return m_scrollerAreaRect; }
    void setScrollerAreaRect(const Rect & rect)
        { m_scrollerAreaRect = rect; }

    Rect thumbUpRect() const
        { return m_thumbUpRect; }
    void setThumbUpRect(const Rect & rect)
        { m_thumbUpRect = rect; }

    Rect thumbDownRect() const
        { return m_thumbDownRect; }
    void setThumbDownRect(const Rect & rect)
        { m_thumbDownRect = rect; }

    int scrollerHeight(int itemHeight, int itemsCount) const {
        int scrollerAreaHeight = height() - ThumbLength*2;
        double ratio = Wt::boundary(double(height())/(itemsCount*itemHeight), 0.0, 1.0);
        return itemsCount ? scrollerAreaHeight * ratio
                          : scrollerAreaHeight;
    }

    int borderOffset() const
        { return BorderOffset; }

private:
    int  m_offset{0};

    Rect m_scrollerAreaRect;
    Rect m_thumbUpRect;
    Rect m_thumbDownRect;

    static const int ThumbLength  = 18;
    static const int BorderOffset = 2;
};

class ListView: public Widget
{
public:
    ListView(Widget * parent);

    void setData(const std::list<std::string> & items);

    int selectedIndex() const;
    void setSelectedIndex(int index);

protected:
    void drawEvent(int x, int y, int width, int height);
    void mousePressEvent(int x, int y, MouseButtons state);
    void mouseReleaseEvent(int x, int y, MouseButtons state);
    void geometryChangeEvent(int x, int y, int width, int height);

private:
    void drawScrollBarFrame(PaintBrush & pb, const Rect & rect) const;
    void drawThumb(PaintBrush & pb, const Rect & rect, bool up) const;
    void drawScroller(PaintBrush & pb, const Rect & rect) const;

    std::list<std::string> m_items;
    int                    m_index{-1};
    int                    m_viewOffset{0};
    int                    m_maxViewOffset{0};
    int                    m_scrollerOffset{0};
    Rect                   m_viewRect;
    ScrollBarGeometry      m_sg;
};

}

#endif
