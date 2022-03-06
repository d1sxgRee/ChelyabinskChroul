#ifndef __NPC_H__
#define __NPC_H__

#include "Creature.hpp"

enum NPC_STATE
{
    Apathy,
    Patrol,
    Fight
}

class NPC : public Creature
{
private:
    NPC_STATE state;
public:
    NPC(Coords _coords, Data _data, std::map < std::string, Animation > _animations, NPC_STATE _state);

    /*You must implement finding paths from a random platform to a random one for the bot,
    using the moveRight, moveLeft, jump functions.
    Also implement a function that determines whether the bot sees the hero.*/
};

NPC::NPC(Coords _coords, Data _data, std::map < std::string, Animation > _animations, NPC_STATE _state) :
    Creature(_coords, _data, _animations), state(_state) {}
#endif //__NPC_H__
