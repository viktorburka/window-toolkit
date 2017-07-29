#include "verification.h"

/*!
    Convernience function to check display pointer.
*/
void check_display_x11(Display * display)
{
    if (display == nullptr) {
        fprintf(stderr, "X11 display is not initialized. Create ApplicationX11 instance first\n");
        exit(-1);
    }
}

/*!
    Convernience function to check graphics context.
*/
void check_gc_x11(GC gc)
{
    if (gc == nullptr) {
        fprintf(stderr, "X11 graphics context is not initialized. Create top level window instance first\n");
        exit(-1);
    }
}

/*!
    Convernience function to check null pointer.
*/
void check_null_ptr(void* ptr)
{
    if (ptr == nullptr)
        abort();
}
