#ifndef __HERO_H__
#define __HERO_H__

#include <ctime>

class Hero : public Creature
{
public:
    Hero(std::map < ATypes, std::pair < Animation, AABB > >, Data, Direction, Condition);
    void update(std::vector < Platform* >, std::vector < Creature* >);
};

Hero::Hero(std::map < ATypes, std::pair < Animation, AABB > > _animations, Data _data, Direction _direction, Condition _condition) :
    Creature(_animations, _data, _direction, _condition) {}

void Hero::update(std::vector < Platform* > platforms, std::vector < Creature* > creatures)
{
    clock_t start = clock();
    if(GetAsyncKeyState(RKEY) && condition == Condition::OnPlatform)
    {
        setDirection(Direction::Right);
        go(true);
    }
    else if(GetAsyncKeyState(LKEY) && condition == Condition::OnPlatform)
    {
        setDirection(Direction::Left);
        go(true);
    }
    else if((GetAsyncKeyState(SKEY) && condition == Condition::OnPlatform &&
    (clock() - start) / CLOCKS_PER_SEC >= slide_cooldown) || slide_state == Sliding::InSlide)
    {
        slide();
    }
    else if(GetAsyncKeyState(JUMP) || condition != Condition::OnPlatform)
    {
        jump(7.0);
    }
    else if(GetAsyncKeyState(AKEY) && (clock() - start) / CLOCKS_PER_SEC >= attack_cooldown)
    {
        attack(creatures);
    }
    else
    {
        animations.at(ATypes::StayRight).first.update(animations.at(ATypes::StayRight).second);
        setLastAnimation(ATypes::StayRight);
    }
    updateAllFixtures();
    updateCondition(platforms);
}

#endif //__HERO_H__
