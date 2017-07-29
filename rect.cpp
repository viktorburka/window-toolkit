#include "rect.h"

#include <string.h>

using namespace Wt;

/*!
    \class Rect
    \inmodule Wt

    \brief The Rect class implements rectangle geometrical object.

    \ingroup widgets

    Rect reprensents a rectangle geomentrical object. For the most
    part its a helper class that conveniently accumulates rectangle
    parameters.
*/

/*!
    Rect constructor.
*/
Rect::Rect(int x, int y, int width, int height)
    : m_x(x)
    , m_y(y)
    , m_width(width)
    , m_height(height)
{
    values = new int[4];
    values[Geometry::xc] = x;
    values[Geometry::yc] = y;
    values[Geometry::w]  = width;
    values[Geometry::h]  = height;
}

/*!
    Rect default constructor. Constructs invalid rectangle
*/
Rect::Rect()
    : m_x(-1)
    , m_y(-1)
    , m_width(-1)
    , m_height(-1)
{
    values = new int[4];
    memset(values, -1, enum_size*sizeof(int));
}

/*!
    Rect copy constructor.
*/
Rect::Rect(const Rect & rect)
    : m_x(rect.m_x)
    , m_y(rect.m_y)
    , m_width(rect.m_width)
    , m_height(rect.m_height)
{
    values = new int[4];
    memcpy(values, rect.values, enum_size*sizeof(int));
}

/*!
    Rect move constructor.
*/
Rect::Rect(Rect && rect)
    : m_x(rect.m_x)
    , m_y(rect.m_y)
    , m_width(rect.m_width)
    , m_height(rect.m_height)
{
    values = rect.values;
    rect.values = nullptr;
}

/*!
    Rect destructor.
*/
Rect::~Rect()
{
    delete [] values;
    values = nullptr;
}

/*!
    Returns rectangle geometry property such as \a x, \a y,
    \a width or \a height.
*/
int Rect::geometry(Geometry g) const
{
    return values[g];
}

/*!
    Sets rectangle geometry property such as \a x, \a y,
    \a width or \a height.
*/
void Rect::setGeometry(Geometry g, int value)
{
    if (g != Geometry::enum_size)
        values[g] = value;
}

/*!
    Returns whether rectangle contains a point with given coordinates.
*/
bool Rect::contains(int x, int y) const
{
    return (x >= m_x && x < m_x+m_width) &&
           (y >= m_y && y < m_y+m_height);
}

/*!
    Assign move operator.
*/
Rect& Rect::operator=(Rect && rect)
{
    m_x = rect.m_x;
    m_y = rect.m_y;
    m_width  = rect.m_width;
    m_height = rect.m_height;

    values = rect.values;
    rect.values = nullptr;
}

/*!
    Assign operator.
*/
Rect& Rect::operator=(const Rect & rect)
{
    m_x = rect.m_x;
    m_y = rect.m_y;
    m_width  = rect.m_width;
    m_height = rect.m_height;

    values = new int[4];
    memcpy(values, rect.values, enum_size*sizeof(int));
}

/*!
    Sets rectangle properties.
*/
void Rect::setRect(int x, int y, int width, int height)
{
    m_x = x;
    m_y = y;
    m_width  = width;
    m_height = height;
}

/*!
    Sets rectangle properties from another Rect object.
*/
void Rect::setRect(const Rect & rect)
{
    setRect(rect.x(), rect.y(), rect.width(), rect.height());
}
