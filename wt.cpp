#include "wt.h"
#include "rect.h"

#include <stdio.h>

using namespace Wt;

WtPrint::~WtPrint()
{
    fprintf(stderr, "\n");
}

WtPrint& WtPrint::operator<<(const Rect & rect)
{
    fprintf(stderr, "Rect(%d, %d, %d, %d) ", rect.x(), rect.y(),
                                             rect.width(), rect.height());
    return *this;
}

WtPrint& WtPrint::operator<<(int number)
{
    fprintf(stderr, "%d ", number);
    return *this;
}

WtPrint& WtPrint::operator<<(const char* str)
{
    fprintf(stderr, "%s ", str);
}

WtPrint& WtPrint::operator<<(const std::string & str)
{
    fprintf(stderr, "%s ", str.c_str());
}
