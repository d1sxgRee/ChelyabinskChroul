#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <vector>
#include "Platform.hpp"
#include "Creature.hpp"

class Level
{
private:
    std::vector < Creature > creatures; // вектор НИПов
    Creature hero;                      // персонаж
    std::vector < Platform > platforms; // платформы чтобы прыгать
public:
    Level(Creature _hero):
        creatures(), hero(_hero), platforms() {}
    void addPlatform(Platform p);
    void addCreature(Creature c);
};

#endif
