#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "TXLib.h"
#include "Creature.hpp"

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
    bool collideWithPlatform(const Creature& cr);
    inline AABB getFixture() { return fixture; };
};

Platform::Platform(AABB _fixture, HDC _sprite) :
    fixture(_fixture), sprite(_sprite)
{
    assert(sprite != nullptr);
}

Platform::~Platform()
{
    txDeleteDC(sprite);
}

//
// TODO: проверить, дабловые ли здесь аргументы или интовые
//

Platform::Platform(const Platform& r) :
    fixture(r.fixture),
    sprite(txCreateCompatibleDC(fixture.maximum.x, fixture.minimum.y))
{
    txBitBlt(sprite, 0, 0, 0, 0, r.sprite);
}

bool Platform::collideWithPlatform(const Creature& cr) :
{
    if(cr.getData().get_velocity_y() > 0)
        return false;
    if(fixture.minimum.y > cr.get_fixture().maximum.y || fixture.minimum.x > cr.get_fixture().maximum.x || fixture.maximum.x < cr.get_fixture().minimum.x)
        return false;
    return true;
}

#endif // __PLATFORM_H__
