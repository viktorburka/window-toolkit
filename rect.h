#ifndef RECT_H
#define RECT_H

namespace Wt {

class Rect
{
public:
    enum Geometry {xc = 0, yc = 1, w = 2, h = 3, enum_size};

    Rect(int x, int y, int width, int height);
    Rect();
    Rect(const Rect & rect);
    Rect(Rect &&);
    ~Rect();

    inline int x() const
        { return m_x; }
    inline int y() const
        { return m_y; }
    inline int width() const
        { return m_width; }
    inline int height() const
        { return m_height; }

    int geometry(Geometry g) const;
    void setGeometry(Geometry g, int value);

    bool contains(int x, int y) const;

    Rect& operator=(Rect && rect);
    Rect& operator=(const Rect & rect);

    void setRect(int x, int y, int width, int height);
    void setRect(const Rect & rect);

private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;

// temp impl
    int* values;
};

}

#endif
