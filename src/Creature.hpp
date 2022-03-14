#ifndef __CREATURE_H__
#define __CREATURE_H__

#include "Coords.hpp"
#include "Globals.hpp"
#include "AABB.hpp"
#include "Animation.hpp"
#include "Data.hpp"
#include "Platform.hpp"
#include <map>
#include <climits>

enum Direction
{
    Right,
    Left,
    None
};

enum Animations
{
    Stay,
    MoveRight,
    MoveLeft,
    Jump,
    AttackRight,
    AttackLeft,
    SlideRight,
    SlideLeft,
    Parry
};

class Creature
{
protected:
    Coords coords;
    Data data;
    AABB fixture;
    Direction direction;
    std::map < Animations, Animation > animations;
    Creature(Coords _coords, Data _data, Direction _direction, std::map < Animations, Animation > _animations);
public:
    virtual ~Creature() {}
    void addAnimation(Animations animation_type, Animation animation);
    void slide();
    void attack();
    void turnRight();
    void turnLeft();
    void go();
    void jump(std::vector < Platform* > platforms, double jump_force);
    virtual void update(std::vector < Platform* > platforms) = 0;
    bool collideWithPlatform(Platform& pl);
    double getJumpLength(double jump_force);
    double getMaxJumpHeight(double jump_force);
    Coords getCoords();
    Data getData();
    AABB get_fixture();
};

Creature::Creature(Coords _coords, Data _data, Direction _direction, std::map < Animations, Animation > _animations) :
    coords(_coords), data(_data), fixture(Coords(coords), Coords(coords.x + animations.at(Stay).getSizeX(), coords.y + animations.at(Stay).getSizeY())),
    direction(_direction), animations(_animations) {}

void Creature::addAnimation(Animations animation_type, Animation animation)
{
    if(animations.count(animation_type) != 0)
        return;
    animations.insert(std::make_pair(animation_type, animation));
}

void Creature::slide()
{
    if(direction == Left)
        animations.at(SlideLeft).update(coords.x, coords.y);
    else if(direction == Right)
        animations.at(SlideRight).update(coords.x, coords.y);
    else return;
}

void Creature::attack()
{
    if(direction == Left)
    {
        animations.at(AttackLeft).update(coords.x, coords.y);
    }
    else if(direction == Right)
    {
        animations.at(AttackRight).update(coords.x, coords.y);
    }
}

void Creature::turnRight() { direction = Right; }

void Creature::turnLeft() { direction = Left; }

void Creature::go()
{
    double e = std::numeric_limits<double>::epsilon();
    if(std::abs(data.get_velocity_y() - 0) <= e)
        return;
    if(direction == Left)
    {
        animations.at(MoveLeft).update(coords.x, coords.y);
        coords.x -= std::abs(data.get_velocity_x());
        data.set_velocity_x(std::abs(data.get_velocity_x()) + std::abs(data.get_acceleration()));
    }
    else if(direction == Right)
    {
        animations.at(MoveRight).update(coords.x, coords.y);
        coords.x += std::abs(data.get_velocity_x());
        data.set_velocity_x(std::abs(data.get_velocity_x()) + std::abs(data.get_acceleration()));
    }
    else return;
}

void Creature::jump(std::vector < Platform* > platforms, double jump_force)
{
    bool on_platform = false;
    unsigned counter = 0;
    if(jump_force < gravity)
        jump_force += gravity;
    data.set_velocity_y(jump_force);
    while(!on_platform || counter == 0)
    {
        for(auto el: platforms)
            if(this->collideWithPlatform(*el))
                on_platform = true;
        if(!on_platform || (on_platform && counter == 0))  //in flight and takeoff
        {
            if(direction == Left)
                coords.x -= data.get_velocity_x();
            else if(direction == Right)
                coords.x += data.get_velocity_x();
            animations.at(Jump).update(coords.x, coords.y);
            coords.y += data.get_velocity_y();
            data.set_velocity_y(data.get_velocity_y() - gravity);
        }
        counter++;
    }
    data.set_velocity_y(0);

}

bool Creature::collideWithPlatform(Platform& pl)
{
    if(getData().get_velocity_y() > 0)
        return false;
    return fixture.collideWithFixture(pl.get_fixture());
}

double Creature::getJumpLength(double jump_force) { return data.get_velocity_x() * (static_cast < int > (jump_force / gravity)); };

double Creature::getMaxJumpHeight(double jump_force)
{
    if(jump_force - gravity > 0 && jump_force - gravity < gravity)
        return jump_force;
    return jump_force + getMaxJumpHeight(jump_force - gravity);
}

Coords Creature::getCoords() { return coords; }

Data Creature::getData() { return data; }

AABB Creature::get_fixture() { return fixture; }

#endif //__CREATURE_H__
