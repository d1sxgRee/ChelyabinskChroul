#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <fstream>
#include <vector>
#include <typeinfo>
#include "Platform.hpp"
#include "Creature.hpp"
#include "Blocks.hpp"

class Level
{
private:
    std::vector < Creature* > creatures; // вектор НИПов
    std::vector < Platform* > platforms; // платформы чтобы прыгать
    std::vector < Blocks > blocks;
public:
    Level(std::vector < Creature* > _creatures, std::vector < Platform* > _platforms, std::vector < Blocks > _blocks);
    void addBlocks(Blocks b);
    void addPlatform(Platform* p);
    void addCreature(Creature* c);
    void deleteBlocks(size_t index);
    void deletePlatform(size_t index);
    void deleteCreature(size_t index);
    std::vector < Platform* > getPlatforms();
    bool visioble(Coords c1, Coords c2);
    void update();
};

Level::Level(std::vector < Creature* > _creatures, std::vector < Platform* > _platforms, std::vector < Blocks > _blocks) :
    creatures(_creatures), platforms(_platforms), blocks(_blocks) {}

void Level::addBlocks(Blocks b) { blocks.push_back(b); }

void Level::addPlatform(Platform* p) { platforms.push_back(p); }

void Level::addCreature(Creature* c)
{
    if(typeid(c).name() == "class Hero *")
        return;
    creatures.push_back(c);
}

void Level::deleteBlocks(size_t index)
{
    assert(index < creatures.size());
    blocks.erase(blocks.begin() + index);
}

void Level::deletePlatform(size_t index)
{
    assert(index < creatures.size());
    platforms.erase(platforms.begin() + index);
}
void Level::deleteCreature(size_t index)
{
    assert(index < creatures.size());
    creatures.erase(creatures.begin() + index);
}

std::vector < Platform* > Level::getPlatforms() { return platforms; }

bool Level::visioble(Coords c1, Coords c2)
{
    double dx = c2.x - c1.x;
    double dy = c2.y - c1.y;
    double k = dx / dy;
    for(auto pl: platforms)
    {
      double day = pl->get_fixture().minimum.y - c1.y;
      double ax = c1.x + k * day;
      if(ax <= pl->get_fixture().maximum.x && ax >= pl->get_fixture().minimum.x)
      {
        return true;
      }
    }
    return false;
}

void Level::update()
{
    for(auto pl: platforms)
        pl->draw();
    for(auto bl: blocks)
        bl.draw(0);
    for(size_t i = 0; i < creatures.size(); i++)
        creatures.at(i)->update();
}

#endif
