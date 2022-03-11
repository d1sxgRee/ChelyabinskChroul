#ifndef __HERO_H__
#define __HERO_H__

class Hero : public Creature
{
public:
    Hero(Coords coords, Data _data, std::map < Animations, Animation > _animations);

    void update() override;
};

void Hero::update()
{
    if(GetAsyncKeyState(RKEY))
    {
        turnRight();
        go();
    }
    if(GetAsyncKeyState(LKEY))
    {
        turnLeft();
        go();
    }
    if(GetASyncKeyState(JUMP))
    {
        jump();
    }
    if(GetAsyncKeyState(AKEY))
    {
        attack();
    }
}

#endif //__HERO_H__
