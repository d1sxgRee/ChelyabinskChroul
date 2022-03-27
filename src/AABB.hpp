#ifndef __AABB_H__
#define __AABB_H__

#include "Coords.hpp"
#include <cassert>

struct Circle { Coords center; double radius; };

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
    bool collideWithCircle(const Circle& c);
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

bool AABB::collideWithCircle(const Circle& c)
{
    assert(c.radius >= 0);

    if(c.center.y < minimum.y)
    {
        if(c.center.x < minimum.x)
            return ((c.center.x - minimum.x) * (c.center.x - minimum.x) +
            (c.center.y - minimum.y) * (c.center.y - minimum.y)) <= c.radius * c.radius;
        if(c.center.x > maximum.x)
            return ((c.center.x - maximum.x) * (c.center.x - maximum.x) +
            (c.center.y - minimum.y) * (c.center.y - minimum.y)) <= c.radius * c.radius;
        return std::abs(minimum.y - c.center.y) <= c.radius;
    }

    if(c.center.y > maximum.y)
    {
        if(c.center.x < minimum.x)
          return ((c.center.x - minimum.x) * (c.center.x - minimum.x) +
          (c.center.y - maximum.y) * (c.center.y - maximum.y)) <= c.radius * c.radius;
        if(c.center.x > maximum.x)
          return ((c.center.x - maximum.x) * (c.center.x - maximum.x) +
          (c.center.y - maximum.y) * (c.center.y - maximum.y)) <= c.radius * c.radius;
        return std::abs(c.center.y - maximum.y) <= c.radius;
    }

    if(c.center.x < minimum.x)
        return std::abs(minimum.x - c.center.x) <= c.radius;

    if(c.center.x > maximum.x)
        return std::abs(c.center.x - maximum.x) <= c.radius;

    return true;
}

#endif //__AABB_H__
