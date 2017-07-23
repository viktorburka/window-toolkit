#ifndef WIDGET_H
#define WIDGET_H

#include "types.h"
#include "bindevent.h"
#include "window.h"
#include "rect.h"

#include <list>
#include <string>
#include <map>
#include <functional>
#include <memory>

namespace Wt {

//class Window;

class Widget
{
public:
    Widget(Widget* parent);
    Widget(int width, int height);

    void show();
    void hide();
    WindowId id() const;
    bool isTopLevel() const;
    bool isVisible() const;

    int width() const;
    int height() const;
    int x() const;
    int y() const;

//    Rect rect() const;

    int dpiX() const;
    int dpiY() const;

    void setSize(int width, int height);
    void setPosition(int x, int y);

    std::string name() const;
    void setName(const std::string & name);

    BindEvent bindEvent(const std::string & name);
    void addEventBinding(const std::string & name, std::function<void()> fn);
    void sendEvent(const std::string & name);

protected:
    virtual void exposeEvent() {}
    virtual void drawEvent(int x, int y, int width, int height) {}
    virtual void closeEvent() {}
    virtual void mousePressEvent(int x, int y, MouseButtons state) {}
    virtual void mouseReleaseEvent(int x, int y, MouseButtons state) {}
    virtual void geometryChangeEvent(int x, int y, int width, int height) {}

    void repaint();

private:
    void drawBackground(int x, int y, int width, int height);

    int     m_x, m_y;
    int     m_width, m_height;
    bool    m_visible;

    //Window* m_platformWin;
    std::unique_ptr<Window> m_platformWin;

    Widget* m_parent;
    std::list<Widget*> m_children;
    std::string m_name;

#ifdef GP_X11
    friend class ApplicationX11;
#endif
    friend class PaintBrush;

    std::list<std::string> m_events;
    std::map<std::string,std::function<void()>> m_bindings;
};

}

#endif
