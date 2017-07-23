#ifndef WINDOW_H
#define WINDOW_H

#include "types.h"

namespace Wt {

class Window
{
public:
    virtual ~Window() {}

    virtual void show() {}
    virtual void hide() {}
    virtual WindowId id() const { return (WindowId)0; }
    virtual bool isTopLevel() const { return false; }
    virtual void setSize(int width, int height) {}
    virtual void setPosition(int x, int y) {}
    virtual int dpiX() const = 0;
    virtual int dpiY() const = 0;

protected:
    virtual void exposeEvent() {}
    virtual void drawEvent(int x, int y, int width, int height) {}
    virtual void closeEvent() {}
    virtual void mousePressEvent(int x, int y, MouseButtons state) {}
    virtual void mouseReleaseEvent(int x, int y, MouseButtons state) {}

    virtual void repaint() {}

private:
    friend class Widget;
};

}

#endif
