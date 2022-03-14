#ifndef __NPC_H__
#define __NPC_H__

#include "Creature.hpp"

enum NPC_STATE
{
    Apathy,
    Patrol,
    Fight
};

class NPC : public Creature
{
private:
    NPC_STATE state;
public:
    NPC(Coords _coords, Data _data, Direction _direction, std::map < Animations, Animation > _animations, NPC_STATE _state);

    void update(std::vector < Platform* > platforms) override;

    /*You must implement finding paths from a random platform to a random one for the bot,
    using the moveRight, moveLeft, jump functions.
    Also implement a function that determines whether the bot sees the hero.*/
};

NPC::NPC(Coords _coords, Data _data, Direction _direction, std::map < Animations, Animation > _animations, NPC_STATE _state) :
    Creature(_coords, _data, _direction, _animations), state(_state) {}

void NPC::update(std::vector < Platform* > platforms)
{
    unsigned platform_number = -1;
    for(size_t i = 0; i < platforms.size(); i++)
        if(this->collideWithPlatform(*platforms.at(i)))
            platform_number = i;
    if(state == Apathy)
    {
        Direction rnd_direction;
        int rnd = rand()%3;

        switch (rnd)
        {
            case 0:
                rnd_direction = Left;
                break;
            case 1:
                rnd_direction = Right;
                break;
            default:
                rnd_direction = None;
                break;
        }

        if(rnd_direction == Left)
        {
            if(coords.x - data.get_velocity_x() >= platforms.at(platform_number)->get_fixture().minimum.x)
            {
                turnLeft();
                go();
            }
            else
                turnRight();
        }
        else if(rnd_direction == Right)
        {
            if(coords.x + data.get_velocity_x() <= platforms.at(platform_number)->get_fixture().maximum.x)
            {
                turnRight();
                go();
            }
            else
                turnLeft();
        }
        else
            jump(platforms, NPC_JUMP_FORCE);
    }

    else if(state == Patrol)
    {
        unsigned go_to_platform = 0;
        if(platform_number + 1 > platforms.size())
        {
            go_to_platform = platform_number - 1;
        }
        if(platforms.at(go_to_platform)->get_fixture().maximum < platforms.at(platform_number)->get_fixture().minimum)
        {
            if(coords.x - data.get_velocity_x() > platforms.at(platform_number)->get_fixture().minimum.x + data.get_velocity_x())
            {
                turnLeft();
                go();
            }
            else if(coords.x - data.get_velocity_x() > platforms.at(platform_number)->get_fixture().minimum.x)
            {
                bool will_be_on_platform = false;
                for(auto el: platforms)
                    if(coords.x + getJumpLength(NPC_JUMP_FORCE) > el->get_fixture().minimum.x &&
                    coords.x + getJumpLength(NPC_JUMP_FORCE) < el->get_fixture().maximum.x)
                        will_be_on_platform = true;
                if(will_be_on_platform)
                {
                    turnLeft();
                    jump(platforms, NPC_JUMP_FORCE);
                }
            }

        }

    }
}

#endif //__NPC_H__
