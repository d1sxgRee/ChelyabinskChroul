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
    inline bool operator==(const Coords& r);
    // пока что будут заглушки
    inline bool operator< (const Coords& r) = delete;
    inline bool operator> (const Coords& r) = delete;
    inline bool operator<=(const Coords& r) = delete;
    inline bool operator>=(const Coords& r) = delete;
};

Coords vec_difference(Coords c1, Coords c2)
{
    Coords c = {c1.x - c2.x, c1.y - c2.y};
    return c;
}

Coords vec_sum(Coords c1, Coords c2)
{
    Coords c = {c1.x + c2.x, c1.y + c2.y};
    return c;
}

double distance(Coords c1, Coords c2)
{
    double d = sqrt(pow(c1.x - c2.x, 2.0) + pow(c1.y - c2.y, 2.0));
    return d;
}

inline bool Coords::operator==(const Coords& r)
{
    double e = std::numeric_limits<double>::epsilon();
    return abs(x - r.x) <= e && abs(y - r.y) <= e;
}

#endif // __COORDS_H__
