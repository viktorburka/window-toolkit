#ifndef WTCOLOR_H
#define WTCOLOR_H

#include <string>

namespace Wt {

class WtColor
{
public:
    WtColor(const std::string & name);

    const char* rgba() const;
    const char* bgra() const;

private:
    char r,g,b,a;
    char m_rgba[4];
    char m_bgra[4];
};

}

#endif
