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
    ARight,
    ALeft
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
    Data data;
    Direction direction;
    Condition condition;

    ATypes last_animation;

    Creature(Data);
    Creature(std::map < ATypes, std::pair < Animation, AABB > >, Data, Direction, Condition);
    virtual ~Creature() = default;
public:
    void updateAllFixtures();
    void setDirection(Direction);
    void setCondition(Condition);
    void setLastAnimation(ATypes);
    void attack(std::vector < Creature* >);
    void go(bool);
    void jump(double jump_force);
    virtual void update(std::vector < Platform* >, std::vector < Creature* >) = 0;
    ATypes getLastAnimation();
    Data getData();
    AABB getFixture(ATypes);
};

Creature::Creature(Data _data) :
    animations(), data(_data), direction(Direction::None),
    condition(Condition::None), last_animation() {}

Creature::Creature( std::map < ATypes, std::pair < Animation, AABB > > _animations,
                    Data _data, Direction _direction, Condition _condition) :
    animations(_animations), data(_data),
    direction(_direction), condition(_condition),
    last_animation() {}

void Creature::updateAllFixtures()
{
    AABB true_fixture = animations.at(last_animation).second;
    for(auto el: animations)
        el.second.second = {true_fixture.minimum, Coords(true_fixture.minimum + (el.second.second.maximum - el.second.second.minimum))};
}

void Creature::setDirection(Direction new_direction) { direction = new_direction; }

void Creature::setCondition(Condition new_condition) { condition = new_condition; }

void Creature::setLastAnimation(ATypes animation_type) { last_animation = animation_type; }

void Creature::attack(std::vector < Creature* > creatures)
{
    go(false);
    switch(direction)
    {
        case Direction::Right:
            animations.at(ATypes::ARight).first.update(animations.at(ATypes::ARight).second);
            for(auto el: creatures)
            {
                if(animations.at(ATypes::ARight).second.collideWithFixture(el->getFixture(el->getLastAnimation())))
                {
                    el->getData().set_health_points(el->getData().get_health_points() - data.get_damage());
                }
            }
            setLastAnimation(ATypes::ARight);
            break;
        case Direction::Left:
            animations.at(ATypes::ALeft).first.update(animations.at(ATypes::ALeft).second);
            for(auto el: creatures)
            {
                if(animations.at(ATypes::ARight).second.collideWithFixture(el->getFixture(el->getLastAnimation())))
                {
                    el->getData().set_health_points(el->getData().get_health_points() - data.get_damage());
                }
            }
            setLastAnimation(ATypes::ALeft);
            break;
        case Direction::None:
            break;
        default: break;
    }
}

void Creature::go(bool with_animation)
{
    switch (direction)
    {
        case Direction::Right:
            animations.at(ATypes::GRight).second.minimum.x += data.get_velocity_x();
            animations.at(ATypes::GRight).second.maximum.x += data.get_velocity_x();
            if(with_animation)
            {
                animations.at(ATypes::GRight).first.update(animations.at(ATypes::GRight).second);
                setLastAnimation(ATypes::GRight);
            }
            break;
        case Direction::Left:
            animations.at(ATypes::GLeft).second.minimum.x -= data.get_velocity_x();
            animations.at(ATypes::GLeft).second.maximum.x -= data.get_velocity_x();
            if(with_animation)
            {
                animations.at(ATypes::GLeft).first.update(animations.at(ATypes::GLeft).second);
                setLastAnimation(ATypes::GLeft);
            }
            break;
        case Direction::None: break;
        default: break;
    }
}

void Creature::jump(double jump_force)
{
    if(condition == Condition::OnPlatform)
    {
        data.set_velocity_y(jump_force);
        animations.at(ATypes::GRight).second.minimum.y -= data.get_velocity_y();
        animations.at(ATypes::GRight).second.maximum.y -= data.get_velocity_y();
        go(false);
        animations.at(ATypes::Jump).first.update(animations.at(ATypes::Jump).second);
        setLastAnimation(ATypes::Jump);
    }
    else
    {
        animations.at(ATypes::GRight).second.minimum.y -= data.get_velocity_y();
        animations.at(ATypes::GRight).second.maximum.y -= data.get_velocity_y();
        data.set_velocity_y(data.get_velocity_y() - gravity);
        go(false);
        if(condition == Condition::InJump)
        {
            animations.at(ATypes::Jump).first.update(animations.at(ATypes::Jump).second);
            setLastAnimation(ATypes::Jump);
        }
        else
        {
            animations.at(ATypes::FreeFall).first.update(animations.at(ATypes::Jump).second);
            setLastAnimation(ATypes::FreeFall);
        }
    }
}

ATypes Creature::getLastAnimation()
{
    return last_animation;
}

Data Creature::getData()
{
    return data;
}

AABB Creature::getFixture(ATypes animation_type)
{
    return animations.at(animation_type).second;
}

#endif //__CREATURE_H__
