#ifndef TYPES_H
#define TYPES_H

#ifdef GP_X11
#include <X11/Xlib.h>
typedef Window WindowId;

enum MouseButton {
    LeftButton = 0x1
};

typedef uint MouseButtons;
#endif

#endif
