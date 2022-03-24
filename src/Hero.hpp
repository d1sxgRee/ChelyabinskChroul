#ifndef __HERO_H__
#define __HERO_H__

#include <ctime>

class Hero : public Creature
{
public:
    Hero(std::map < ATypes, std::pair < Animation, AABB > >, Data, Direction, Condition);
    void update(std::vector < Platform* >, std::vector < Creature* >) override;
};

Hero::Hero(std::map < ATypes, std::pair < Animation, AABB > > _animations, Data _data, Direction _direction, Condition _condition) :
    Creature(_animations, _data, _direction, _condition) {}

void Hero::update(std::vector < Platform* > platforms, std::vector < Creature* > creatures)
{
    clock_t start = clock();
    if(GetAsyncKeyState(RKEY))
    {
        setDirection(Direction::Right);
        go(true);
    }
    else if(GetAsyncKeyState(LKEY))
    {
        setDirection(Direction::Left);
        go(true);
    }
    else if(GetAsyncKeyState(SKEY) && (clock() - start) / CLOCKS_PER_SEC >= slide_cooldown)
    {
        /*slide*/
    }
    else if(GetAsyncKeyState(JUMP) || condition != Condition::OnPlatform)
    {
        jump(7.0);
    }
    else if(GetAsyncKeyState(AKEY) && (clock() - start) / CLOCKS_PER_SEC >= attack_cooldown)
    {
        attack(creatures);
    }
    updateAllFixtures();
    updateCondition(platforms);
}

#endif //__HERO_H__
