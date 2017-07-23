#ifndef VERIFICAITON_H
#define VERIFICAITON_H

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

void check_display_x11(Display * display);
void check_gc_x11(GC gc);
void check_null_ptr(void* ptr);

#endif
