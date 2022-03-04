#ifndef __AABB_H__
#define __AABB_H__

#include "Coords.hpp"
#include <cassert>

class AABB
{
public:
    Coords minimum;
    Coords maximum;

    AABB(Coords, Coords);
    AABB(const AABB& a);
    inline AABB operator= (const AABB& a);
    bool collideWithFixture(const AABB& a);
};

AABB::AABB(Coords _minimum, Coords _maximum) :
    minimum(_minimum), maximum(_maximum)
{
    assert(minimum != maximum);
    if(minimum > maximum)
    {
        Coords temp = minimum;
        minimum = maximum;
        maximum = temp;
    }
}

AABB::AABB(const AABB& a) :
    minimum(a.minimum), maximum(a.maximum) {}

inline AABB AABB::operator= (const AABB& a)
{
    minimum = a.minimum;
    maximum = a.maximum;
    return *this;
}

bool AABB::collideWithFixture(const AABB& a)
{
    if((minimum.x < a.maximum.x || maximum.x > a.minimum.x) && (minimum.y < a.maximum.y || maximum.y > a.minimum.y))
        return true;
    else if((minumum.x > a.maximum.x && minimum.x < a.minimum.x) && (a.minimum.y < minimum.y && a.minimum.y > maximum.y))
        return true;
    else if((minumum.y > a.maximum.y && minimum.y < a.minimum.y) && (a.minimum.x < minimum.x && a.minimum.x > maximum.x))
        return true
    return false;
}
#endif //__AABB_H__
