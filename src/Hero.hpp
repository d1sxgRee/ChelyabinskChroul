#ifndef __HERO_H__
#define __HERO_H__

class Hero : public Creature
{
public:
    Hero(Coords coords, Data _data, std::map < Animations, Animation > _animations);

    void slide();
    void update() override;
};

void Hero::slide()
{
    if(direction == Left)
        animations.at(SlideLeft).update(coords.x, coords.y);
    else if(direction == Right)
        animations.at(SlideRight).update(coords.x, coords.y);
    else return;
}

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
