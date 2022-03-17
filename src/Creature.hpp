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

enum class Direction
{
    None,
    Right,
    Left
};

enum class ATypes
{
    Stay,
    GRight,
    GLeft,
    Jump,
    FreeFall,
    Slide,
    Parry,
    Attack
};

enum class Condition
{
    None,
    FreeFall,
    InJump,
    OnPlatform
};

class Creature
{
protected:
    std::map < ATypes, std::pair < Animation, AABB > > animations;
    Coords coords;
    Data data;
    Direction direction;
    Condition condition;

    Creature(Coords, Data);
    Creature(std::map < ATypes, std::pair < Animation, AABB > >, Coords, Data, Direction, Condition);
public:
    void setDirection(Direction);
    void setCondition(Condition);
    void go();
    void jump(double jump_force);
    virtual void update(std::vector < Platform* >) = 0;
};

Creature::Creature(Coords _coords, Data _data) :
    animations(), coords(_coords),
    data(_data), direction(Direction::None), condition(Condition::None) {}

Creature::Creature( std::map < ATypes, std::pair < Animation, AABB > > _animations,
                    Coords _coords, Data _data, Direction _direction, Condition _condition) :
    animations(_animations), coords(_coords), data(_data),
    direction(_direction), condition(_condition) {}

void Creature::setDirection(Direction new_direction) { direction = new_direction; }

void Creature::setCondition(Condition new_condition) { condition = new_condition; }

void Creature::go()
{
    switch (direction)
    {
        case Direction::Right:
            coords.x += data.get_velocity_x();
            animations.at(ATypes::GRight).first.update(coords.x, coords.y);
            break;
        case Direction::Left:
            coords.x += data.get_velocity_x();
            animations.at(ATypes::GLeft).first.update(coords.x, coords.y);
            break;
        default: break;
    }
}

void Creature::jump(double jump_force)
{
    if(condition == Condition::OnPlatform)
    {
        data.set_velocity_y(jump_force);
        coords.y -= data.get_velocity_y();
        animations.at(ATypes::Jump).first.update(coords.x, coords.y);
    }
    else
    {
        coords.y -= data.get_velocity_y();
        data.set_velocity_y(data.get_velocity_y() - gravity);
        if(condition == Condition::InJump)
            animations.at(ATypes::Jump).first.update(coords.x, coords.y);
        else
            animations.at(ATypes::FreeFall).first.update(coords.x, coords.y);
    }
}

#endif //__CREATURE_H__
