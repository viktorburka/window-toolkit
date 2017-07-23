#ifndef DISPLAYX11_H
#define DISPLAYX11_H

#include <X11/Xlib.h>

namespace Wt {

class DisplayX11
{
public:
    static Display* currentDisplay();
    static GC currentGC();
    static Font defaultFont();
    static void initWindowManager(Display* display);
    
    static Display* display;
    static GC gc;
    static Atom closeWinMsg;
    //static Font font;
    static XFontStruct* fontInfo;
};

}

#endif
