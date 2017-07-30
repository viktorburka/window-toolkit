#include "wt.h"
#include "rect.h"

#include <stdio.h>

using namespace Wt;

/*!
    \class WtPrint
    \inmodule Wt

    \brief The WtPrint class prints application output.

    \ingroup tools

    WtPrint can print application output. It prints to the console by default
    and has a veriety of overloaded methods that understand different types.

    Using WtPrint is easy just call it by using stream \a << operator like this:

    \code Rect rect(0,0,100,100);
    \code ...
    \code WtPrint() << "This is my widget rectangle:" << rect;

    In this eaxmples it takes char* first and then structure of type Rect and
    conveniently prints it eleminating the need to put long statements to print
    each property of Rect like \a x, \a y, \a width, \a height.

    Once WtPrint is finished, it will conveniently put a new line.
*/

/*!
    WtPrint destructor. Conveniently puts newline to start next print statement.
*/
WtPrint::~WtPrint()
{
    fprintf(stderr, "\n");
}

/*!
    Stream overloaded operator for printing Rect type.
*/
WtPrint& WtPrint::operator<<(const Rect & rect)
{
    fprintf(stderr, "Rect(%d, %d, %d, %d) ", rect.x(), rect.y(),
                                             rect.width(), rect.height());
    return *this;
}

/*!
    Stream overloaded operator for printing int type.
*/
WtPrint& WtPrint::operator<<(int number)
{
    fprintf(stderr, "%d ", number);
    return *this;
}

/*!
    Stream overloaded operator for printing char* type.
*/
WtPrint& WtPrint::operator<<(const char* str)
{
    fprintf(stderr, "%s ", str);
}

/*!
    Stream overloaded operator for printing std::string type.
*/
WtPrint& WtPrint::operator<<(const std::string & str)
{
    fprintf(stderr, "%s ", str.c_str());
}
