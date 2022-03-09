#ifndef __CREATURE_H__
#define __CREATURE_H__

#include "Coords.hpp"
#include "Globals.hpp"
#include "AABB.hpp"
#include "Animation.hpp"
#include "Data.hpp"
#include "Level.hpp"
#include <map>

class Creature
{
private:
    Coords coords;
    Data data;
    AABB fixture;
    std::map < std::string, Animation > animations;
public:
    Creature(Coords _coords, Data _data, std::map < std::string, Animation > _animations);

    void addAnimation(std::string name, Animation animation);
    void moveRight();
    void moveLeft();
    void jump();
    void keys_interaction(int rkey, int lkey);
    bool collideWithPlatform(const Platform& pl);
    Coords getCoords();
    Data getData();
    AABB get_fixture();
};

Creature::Creature(Coords _coords, Data _data, std::map < std::string, Animation > _animations) :
    coords(_coords), data(_data), fixture(_fixture), animations(_animations)
    {
        AABB fixture(coords, coords.x + getSizeX(), coords.y + getSizeY());
    }

void Creature::addAnimation(std::string name, Animation animation)
{
    if(animations.count(name) != 0)
        return;
    animations.insert(std::make_pair(name, animation));
}

void Creature::moveRight()
{
    coords.x += std::abs(data.get_velocity_x());
    data.set_velocity_x(std::abs(data.get_velocity_x()) + std::abs(data.get_acceleration()));
}
void Creature::moveLeft()
{
    coords.x -= std::abs(data.get_velocity_x());
    data.set_velocity_x(std::abs(data.get_velocity_x()) + std::abs(data.get_acceleration()));
}

void Creature::jump(Level level)
{
    /*Please create creature jump!*/
}

bool Creature::collideWithPlatform(const Platform& pl) :
{
    if(getData().get_velocity_y() > 0)
        return false;
    if(fixture.maximum.y < pl.get_fixture().minimum.y || fixture.maximum.y > pl.get_fixture().maximum.y)
        return false;
    if(fixture.minimum.x > pl.get_fixture().maximum.x || fixture.maximum.x < pl.get_fixture().minimum.x)
        return false;
    return true;
}

Coords Creature::getCoords() { return coords; }
Data Creature::getData() { return data; }
AABB Creature::get_fixture() { return fixture; }

#endif //__CREATURE_H__
