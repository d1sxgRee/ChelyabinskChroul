#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <fstream>
#include <vector>
#include <typeinfo>
#include "Platform.hpp"
#include "Creature.hpp"

class Level
{
private:
    std::vector < Creature* > creatures; // вектор НИПов
    std::vector < Platform* > platforms; // платформы чтобы прыгать
public:
    Level(std::vector < Creature* > _creatures, std::vector < Platform* > _platforms);
    void addPlatform(Platform* p);
    void addCreature(Creature* c);
    std::vector < Platform* > getPlatforms();
    void update();
};

Level::Level(std::vector < Creature* > _creatures, std::vector < Platform* > _platforms) :
    creatures(_creatures), platforms(_platforms) {}

void Level::addPlatform(Platform* p) { platforms.push_back(p); }

void Level::addCreature(Creature* c)
{
    if(typeid(c).name() == "class Hero")
        return;
    creatures.push_back(c);
}

std::vector < Platform* > Level::getPlatforms() { return platforms; }

void Level::update()
{
    for(auto pl: platforms)
        pl->draw();
    for(size_t i = 0; i < creatures.size(); i++)
        creatures.at(i)->update();
}

#endif
