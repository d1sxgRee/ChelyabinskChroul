#ifndef __COORDS_H__
#define __COORDS_H__

#include <cmath>
#include <limits>

// coords header includes Coords class and some functions to make it easier to work with it

class Coords
{
public:
    double x;
    double y;
    // операторы арефметических действий
    Coords operator+ (const Coords& r);
    Coords operator- (const Coords& r);
    // операторы сравнения
    inline bool operator==(const Coords& r);
    // пока что будут заглушки
    inline bool operator< (const Coords& r) = delete;
    inline bool operator> (const Coords& r) = delete;
    inline bool operator<=(const Coords& r) = delete;
    inline bool operator>=(const Coords& r) = delete;
};

double distance(Coords c1, Coords c2)
{
    double d = sqrt(pow(c1.x - c2.x, 2.0) + pow(c1.y - c2.y, 2.0));
    return d;
}

Coords Coords::operator- (const Coords& r)
{
    Coords c = {x - r.x, y - r.y};
    return c;
}

Coords Coords::operator+ (const Coords& r)
{
    Coords c = {x + r.x, y + r.y};
    return c;
}

inline bool Coords::operator==(const Coords& r)
{
    double e = std::numeric_limits<double>::epsilon();
    return abs(x - r.x) <= e && abs(y - r.y) <= e;
}

#endif // __COORDS_H__
