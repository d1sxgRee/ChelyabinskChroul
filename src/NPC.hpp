#ifndef __NPC_H__
#define __NPC_H__

#include "Creature.hpp"

enum class States
{
    Patrooling,
    Attacking,
    Fleeing,
    Idling,
    Searching
};

class NPC
{
public:
    NPC(std::map < ATypes, std::pair < Animation, AABB > >, Data, Direction, Condition);
};

#endif //__NPC_H__
