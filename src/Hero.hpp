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
    if(GetAsyncKeyState(JUMP))
    {
        jump();
    }
    if(GetAsyncKeyState(AKEY))
    {
        attack();
    }
    if(GetAsyncKeyState(SKEY))
    {
        slide();
    }
    else
    {
        animations.at(Stay).update(coords.x, coords.y);
    }
}

#endif //__HERO_H__
