#ifndef WTX11DRIVER_H
#define WTX11DRIVER_H

#include "widget.h"

using namespace Wt;

class WtDriverWidget: public Widget
{
public:
    WtDriverWidget(int width, int height);

protected:
    void drawEvent(int x, int y, int width, int height);
};

#endif
