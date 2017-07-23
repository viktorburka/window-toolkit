#include "rect.h"

#include <string.h>

using namespace Wt;

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

Rect::Rect()
    : m_x(-1)
    , m_y(-1)
    , m_width(-1)
    , m_height(-1)
{
    values = new int[4];
    memset(values, -1, enum_size*sizeof(int));
}

Rect::Rect(const Rect & rect)
    : m_x(rect.m_x)
    , m_y(rect.m_y)
    , m_width(rect.m_width)
    , m_height(rect.m_height)
{
    values = new int[4];
    memcpy(values, rect.values, enum_size*sizeof(int));
}

Rect::Rect(Rect && rect)
    : m_x(rect.m_x)
    , m_y(rect.m_y)
    , m_width(rect.m_width)
    , m_height(rect.m_height)
{
    values = rect.values;
    rect.values = nullptr;
}

Rect::~Rect()
{
    delete [] values;
    values = nullptr;
}

int Rect::geometry(Geometry g) const
{
    return values[g];
}

void Rect::setGeometry(Geometry g, int value)
{
    if (g != Geometry::enum_size)
        values[g] = value;
}

bool Rect::contains(int x, int y) const
{
    return (x >= m_x && x < m_x+m_width) &&
           (y >= m_y && y < m_y+m_height);
}

Rect& Rect::operator=(Rect && rect)
{
    m_x = rect.m_x;
    m_y = rect.m_y;
    m_width  = rect.m_width;
    m_height = rect.m_height;

    values = rect.values;
    rect.values = nullptr;
}

Rect& Rect::operator=(const Rect & rect)
{
    m_x = rect.m_x;
    m_y = rect.m_y;
    m_width  = rect.m_width;
    m_height = rect.m_height;

    values = new int[4];
    memcpy(values, rect.values, enum_size*sizeof(int));
}

void Rect::setRect(int x, int y, int width, int height)
{
    m_x = x;
    m_y = y;
    m_width  = width;
    m_height = height;
}

void Rect::setRect(const Rect & rect)
{
    setRect(rect.x(), rect.y(), rect.width(), rect.height());
}
