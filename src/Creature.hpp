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
    StayRight,
    StayLeft,
    GRight,
    GLeft,
    Jump,
    FreeFall,
    SRight,
    SLeft,
    Parry,
    ARight,
    ALeft,
    HurtRight,
    HurtLeft
};

enum class Condition
{
    None,
    FreeFall,
    InJump,
    OnPlatform
};

enum class Sliding
{
    None,
    InSlide
};

class Creature
{
protected:
    std::map < ATypes, std::pair < Animation, AABB > > animations;
    Data data;
    Direction direction;
    Condition condition;
    Sliding slide_state;

    ATypes last_animation;

    Creature(Data);
    Creature(std::map < ATypes, std::pair < Animation, AABB > >, Data, Direction, Condition);
    virtual ~Creature() = default;
public:
    void updateFixture(ATypes, ATypes);
    void updateAllFixtures();
    void updateCondition(std::vector < Platform* >);
    void setDirection(Direction);
    void setCondition(Condition);
    void setLastAnimation(ATypes);
    void attack(std::vector < Creature* >);
    void go(bool);
    void jump(double jump_force);
    void slide();
    double getMaxJumpHeight(double);
    double getJumpWidth(double, double);
    Direction getDirection();
    Condition getCondition();
    ATypes getLastAnimation();
    Data getData();
    AABB getFixture(ATypes);
    Coords getCoords();
};

Creature::Creature(Data _data) :
    animations(), data(_data), direction(Direction::None),
    condition(Condition::None), slide_state(Sliding::None),
    last_animation(ATypes::StayRight) {}

Creature::Creature( std::map < ATypes, std::pair < Animation, AABB > > _animations,
                    Data _data, Direction _direction, Condition _condition) :
    animations(_animations), data(_data),
    direction(_direction), condition(_condition),
    slide_state(Sliding::None), last_animation(ATypes::StayRight) {}

void Creature::updateFixture( ATypes false_animation, ATypes true_animation)
{
    animations.at(false_animation).second = {animations.at(true_animation).second.minimum,
    Coords(animations.at(true_animation).second.minimum +
    (animations.at(false_animation).second.maximum - animations.at(false_animation).second.minimum))};
}

void Creature::updateAllFixtures()
{
    AABB true_fixture = animations.at(last_animation).second;
    for(auto el: animations)
        el.second.second = {true_fixture.minimum, Coords(true_fixture.minimum + (el.second.second.maximum - el.second.second.minimum))};
}

void Creature::updateCondition(std::vector < Platform* > platforms)
{
    if(condition != Condition::OnPlatform)
    {
        for(auto el: platforms)
        {
            if(animations.at(last_animation).second.collideWithFixture(el->get_fixture()))
            {
                condition = Condition::OnPlatform;
                return;
            }
        }
    }
    if(data.get_velocity_y() < 0)
    {
        condition = Condition::FreeFall;
        return;
    }
    else if(data.get_velocity_y() >= 0)
        condition = Condition::InJump;
}

void Creature::setDirection(Direction new_direction) { direction = new_direction; }

void Creature::setCondition(Condition new_condition) { condition = new_condition; }

void Creature::setLastAnimation(ATypes animation_type) { last_animation = animation_type; }

void Creature::attack(std::vector < Creature* > creatures)
{
    go(false);
    if(direction == Direction::Right)
        updateFixture(ATypes::ARight, ATypes::GRight);
    else if(direction == Direction::Left)
        updateFixture(ATypes::ALeft, ATypes::GLeft);
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
        animations.at(ATypes::Jump).second.minimum.y -= data.get_velocity_y();
        animations.at(ATypes::Jump).second.maximum.y -= data.get_velocity_y();
        go(false);
        if(direction == Direction::Right)
            updateFixture(ATypes::Jump, ATypes::GRight);
        else if(direction == Direction::Left)
            updateFixture(ATypes::Jump, ATypes::GLeft);
        animations.at(ATypes::Jump).first.update(animations.at(ATypes::Jump).second);
        setLastAnimation(ATypes::Jump);
    }
    else
    {
        animations.at(ATypes::Jump).second.minimum.y -= data.get_velocity_y();
        animations.at(ATypes::Jump).second.maximum.y -= data.get_velocity_y();
        data.set_velocity_y(data.get_velocity_y() - gravity);
        go(false);
        if(direction == Direction::Right)
            updateFixture(ATypes::Jump, ATypes::GRight);
        else if(direction == Direction::Left)
            updateFixture(ATypes::Jump, ATypes::GLeft);
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

void Creature::slide()
{
    switch(direction)
    {
        case Direction::Right:
            slide_state = Sliding::InSlide;
            animations.at(ATypes::SRight).second.minimum.x += data.get_velocity_x() * 2;
            animations.at(ATypes::SRight).second.maximum.x += data.get_velocity_x() * 2;
            animations.at(ATypes::SRight).first.update(animations.at(ATypes::SRight).second);
            if(animations.at(ATypes::SRight).first.isEnd())
                slide_state = Sliding::None;
            break;
        case Direction::Left:
            slide_state = Sliding::InSlide;
            animations.at(ATypes::SLeft).second.minimum.x += data.get_velocity_x() * 2;
            animations.at(ATypes::SLeft).second.maximum.x += data.get_velocity_x() * 2;
            animations.at(ATypes::SLeft).first.update(animations.at(ATypes::SLeft).second);
            if(animations.at(ATypes::SLeft).first.isEnd())
                slide_state = Sliding::None;
            break;
        case Direction::None: break;
        default: break;
    }
}

double Creature::getMaxJumpHeight(double jump_force)
{
    return (jump_force * jump_force) / (2 * gravity);
}

double Creature::getJumpWidth(double ydelta, double jump_force)
{
    if(ydelta < data.get_velocity_y())
        return data.get_velocity_x();
    return data.get_velocity_x() + getJumpWidth(ydelta - jump_force, jump_force - gravity);
}

Direction Creature::getDirection()
{
    return direction;
}

Condition Creature::getCondition()
{
    return condition;
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

Coords Creature::getCoords()
{
    AABB f = animations.at(last_animation).second;
    return (Coords) {f.minimum.x, f.minimum.y};
}

#endif //__CREATURE_H__
