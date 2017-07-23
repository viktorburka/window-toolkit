#ifndef WT_H
#define WT_H

#include <string>

namespace Wt {

class Rect;

template<typename T>
T boundary(T value, T min, T max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

class WtPrint
{
public:
    ~WtPrint();

    WtPrint& operator<<(const Rect & rect);
    WtPrint& operator<<(int number);
    WtPrint& operator<<(const char* str);
    WtPrint& operator<<(const std::string & str);
};

}

#endif
