#ifndef __CREATURE_H__
#define __CREATURE_H__

#include "Coords.hpp"
#include "Globals.hpp"
#include "AABB.hpp"
#include "Animation.hpp"
#include "Data.hpp"
#include <map>

class Creature
{
private:
    Coords coords;
    Data data;
    std::map < std::string, Animation > animations;
public:
    Creature(Coords _coords, Data _data, std::map < std::string, Animation > _animations);

    void addAnimation(std::string name, Animation animation);
    void moveRight();
    void moveLeft();
    void keys_interaction(int rkey, int lkey);
    Coords getCoords();
    Data getData();
};

Creature::Creature(Coords _coords, Data _data, std::map < std::string, Animation > _animations) :
    coords(_coords), data(_data), animations(_animations) {}

void Creature::addAnimation(std::string name, Animation animation)
{
    if(animations.count(name) != 0)
        return;
    animations.insert(std::make_pair(name, animation));
}

void Creature::moveRight()
{
    coords.x += std::abs(data.get_velocity());
    coords.y += std::abs(data.get_velocity()) / WindowR;
    data.set_velocity(std::abs(data.get_velocity()) + std::abs(data.get_acceleration()));
}
void Creature::moveLeft()
{
    coords.x -= std::abs(data.get_velocity());
    coords.y -= std::abs(data.get_velocity()) / WindowR;
    data.set_velocity(std::abs(data.get_velocity()) + std::abs(data.get_acceleration()));
}

void Creature::keys_interaction(int rkey, int lkey)
{
    if(GetAsyncKeyState(rkey))
    {
        for(auto el: animations)
        {
            if(el.first == "moveRight" || el.first == "moveright" ||
            el.first == "MoveRight", el.first == "Moveright")
                el.second.update(coords.x, coords.y);
        }
        moveRight();
    }
    else if(GetAsyncKeyState(lkey))
    {
        for(auto el: animations)
        {
            if(el.first == "moveLeft" || el.first == "moveleft" ||
            el.first == "MoveLeft", el.first == "Moveleft")
                el.second.update(coords.x, coords.y);
        }
        moveLeft();
    }
}

Coords Creature::getCoords() { return coords; }
Data Creature::getData() { return data; }

#endif //__CREATURE_H__
