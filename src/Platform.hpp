#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "TXLib.h"
#include "Coords.hpp"

class Platform
{
private:
    AABB fixture;
    HDC sprite;
public:
    // всякие конструкторы, деструкторы и прочая шелуха
    Platform(AABB _fixture, HDC _sprite);
    ~Platform();
    Platform(const Platform& r);
    // этот вроде бы не нужный
    Platform& operator= (const Platform& r) = delete;
    // нормальные мужыцкие методы для мужиков
    inline AABB getFixture() { return fixture; };
};

Platform::Platform(AABB _fixture, HDC _sprite) :
    fixture(_fixture), sprite(_sprite)
{
    assert(sprite != nullptr);
}

Platform::Platform(const Platform& r) :
    fixture(r.fixture), sprite(txCreateCompatibleDC(a.endX, a.height))
{
    txBitBlt(sprite, 0, 0, 0, 0, r.sprite);
}

Platform::~Platform()
{
    txDeleteDC(sprite);
}

//
// TODO: проверить, дабловые ли здесь аргументы или интовые
//

Platform::Platform(const Platform& r):
    fixture(r.fixture),
    sprite(txCreateCompatibleDC(fixture.maximum.x, fixture.minimum.y))
{
    txBitBlt(sprite, 0, 0, 0, 0, r.sprite);
}

#endif // __PLATFORM_H__
