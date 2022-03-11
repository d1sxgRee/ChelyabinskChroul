#ifndef __AABB_H__
#define __AABB_H__

#include "Coords.hpp"
#include <cassert>

class AABB
{
public:
    Coords minimum;
    Coords maximum;

    AABB();
    AABB(Coords, Coords);
    AABB(const AABB& a);
    inline AABB& operator= (const AABB& a);
    bool collideWithFixture(const AABB& a);
};

AABB::AABB() :
    minimum(), maximum() {}

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

inline AABB& AABB::operator= (const AABB& a)
{
    minimum = a.minimum;
    maximum = a.maximum;
    return *this;
}

bool AABB::collideWithFixture(const AABB& a)
{
    if(maximum.x < a.minimum.x || minimum.x > a.maximum.x)
        return false;
    if(maximum.y < a.minimum.y || minimum.y > a.maximum.y)
        return false;
    return true;
}
#endif //__AABB_H__
