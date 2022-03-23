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
    bool collideWithCircle(Coords center, double radius);
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

bool AABB::collideWithCircle(Coords center, double radius)
{
    assert(radius >= 0);
    if(center.y < minimum.y)
    {
        if(center.x < minimum.x)
            return ((center.x - minimum.x) * (center.x - minimum.x) +
            (center.y - minimum.y) * (center.y - minimum.y)) <= radius * radius;
        if(center.x > maximum.x)
            return ((center.x - maximum.x) * (center.x - maximum.x) +
            (center.y - maximum.y) * (center.y - maximum.y)) <= radius * radius;
        return minimum.y - center.y <= radius;
    }
    if(center.y > maximum.y)
    {
        if(center.x < minimum.x)
          return ((center.x - minimum.x) * (center.x - minimum.x) +
          (center.y - maximum.y) * (center.y - maximum.y)) <= radius * radius;
        if(center.x > maximum.x)
          return ((center.x - maximum.x) * (center.x - maximum.x) +
          (center.y - maximum.y) * (center.y - maximum.y)) <= radius * radius;
        return center.y - maximum.y <= radius;
    }

    if(center.x < minimum.x)
        return minimum.x - center.x <= radius;
    if(center.x > maximum.x)
        return center.x - maximum.x <= radius;
    return center.x - minimum.x <= radius || maximum.x - center.x <= radius ||
    center.y - minimum.y <= radius || maximum.y - center.y <= radius;
}
#endif //__AABB_H__
