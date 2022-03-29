#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <fstream>
#include <vector>
#include <typeinfo>
#include "Globals.hpp"
#include "Platform.hpp"
#include "Creature.hpp"
#include "NPC.hpp"
#include "Blocks.hpp"

class Level
{
private:
    std::vector < NPC* > creatures; // вектор НИПов
    std::vector < Platform* > platforms; // платформы чтобы прыгать
    std::vector < Blocks > blocks;

    std::vector < std::vector < size_t > > possible_transitions;
public:
    Level(std::vector < NPC* > _creatures, std::vector < Platform* > _platforms, std::vector < Blocks > _blocks);
    void addBlocks(Blocks b);
    void addPlatform(Platform* p);
    void addCreature(NPC* npc);
    void deleteBlocks(size_t index);
    void deletePlatform(size_t index);
    void deleteCreature(size_t index);
    std::vector < Platform* > getPlatforms();
    std::vector < Creature* > getCreatures();
    bool visioble(Coords c1, Coords c2);
    void update(Hero& hero);
};

Level::Level(std::vector < NPC* > _creatures, std::vector < Platform* > _platforms, std::vector < Blocks > _blocks) :
    creatures(_creatures), platforms(_platforms), blocks(_blocks), possible_transitions()
{
    possible_transitions.reserve(0);
    possible_transitions.resize(0);
    for(size_t i = 0; i < platforms.size(); i++)
    {
        for(size_t j = 0; j < platforms.size(); j++)
        {
            if(i == j)
                continue;
            if(platforms.at(i)->get_fixture().minimum.y > platforms.at(j)->get_fixture().maximum.y)
            {
                if(platforms.at(i)->get_fixture().minimum < platforms.at(j)->get_fixture().minimum)
                {
                    if(platforms.at(i)->get_fixture().minimum.y - creatures.at(0)->getMaxJumpHeight(NPC_JUMP_FORCE) <= platforms.at(j)->get_fixture().minimum.y &&
                    platforms.at(i)->get_fixture().minimum.x + creatures.at(0)->getData().get_velocity_x() +
                    creatures.at(0)->getJumpWidth(platforms.at(i)->get_fixture().minimum.y - platforms.at(j)->get_fixture().minimum.y, NPC_JUMP_FORCE) >=
                    platforms.at(j)->get_fixture().minimum.x)
                        possible_transitions.at(i).push_back(j);
                    else continue;
                }
                else if(platforms.at(i)->get_fixture().maximum > platforms.at(j)->get_fixture().maximum)
                {
                    if(platforms.at(i)->get_fixture().minimum.y - creatures.at(0)->getMaxJumpHeight(NPC_JUMP_FORCE) <= platforms.at(j)->get_fixture().minimum.y &&
                    platforms.at(i)->get_fixture().maximum.x - creatures.at(0)->getData().get_velocity_x() + creatures.at(0)->getJumpWidth(
                    platforms.at(i)->get_fixture().minimum.y - platforms.at(j)->get_fixture().minimum.y, NPC_JUMP_FORCE) >= platforms.at(j)->get_fixture().minimum.x)
                        possible_transitions.at(i).push_back(j);
                    else continue;
                }
                else
                {
                    if(platforms.at(i)->get_fixture().minimum.y - creatures.at(0)->getMaxJumpHeight(NPC_JUMP_FORCE) <= platforms.at(j)->get_fixture().minimum.y)
                        possible_transitions.at(i).push_back(j);
                    else continue;
                }
            }
            else if(platforms.at(i)->get_fixture().maximum.y < platforms.at(j)->get_fixture().minimum.y)
            {
                if(platforms.at(i)->get_fixture().minimum < platforms.at(j)->get_fixture().minimum)
                {
                    if(platforms.at(i)->get_fixture().maximum.x - creatures.at(0)->getData().get_velocity_x() +
                    creatures.at(0)->getJumpWidth(platforms.at(j)->get_fixture().minimum.y - platforms.at(i)->get_fixture().minimum.y, NPC_JUMP_FORCE) <=
                    platforms.at(j)->get_fixture().maximum.x - creatures.at(0)->getData().get_velocity_x())
                        possible_transitions.at(i).push_back(j);
                    else continue;
                }
                else if(platforms.at(i)->get_fixture().maximum > platforms.at(j)->get_fixture().minimum)
                {
                    if(platforms.at(i)->get_fixture().minimum.x + creatures.at(0)->getData().get_velocity_x() +
                    creatures.at(0)->getJumpWidth(platforms.at(j)->get_fixture().minimum.y - platforms.at(i)->get_fixture().minimum.y, NPC_JUMP_FORCE) <=
                    platforms.at(j)->get_fixture().maximum.x - creatures.at(0)->getData().get_velocity_x())
                        possible_transitions.at(i).push_back(j);
                    else continue;
                }
                else continue;
            }
            else
            {
                if(platforms.at(i)->get_fixture().minimum < platforms.at(j)->get_fixture().minimum)
                {
                    if(platforms.at(i)->get_fixture().maximum.x - creatures.at(0)->getData().get_velocity_x() +
                    creatures.at(0)->getJumpWidth(creatures.at(0)->getMaxJumpHeight(NPC_JUMP_FORCE), NPC_JUMP_FORCE)  <=
                    platforms.at(j)->get_fixture().maximum.x - creatures.at(0)->getData().get_velocity_x())
                        possible_transitions.at(i).push_back(j);
                    else continue;
                }
                else if(platforms.at(i)->get_fixture().maximum > platforms.at(j)->get_fixture().maximum)
                {
                    if(platforms.at(i)->get_fixture().minimum.x + creatures.at(0)->getData().get_velocity_x() +
                    creatures.at(0)->getJumpWidth(creatures.at(0)->getMaxJumpHeight(NPC_JUMP_FORCE), NPC_JUMP_FORCE) <=
                    platforms.at(j)->get_fixture().maximum.x - creatures.at(0)->getData().get_velocity_x())
                        possible_transitions.at(i).push_back(j);
                    else continue;
                }
                else possible_transitions.at(i).push_back(j);
            }
        }
    }
}

void Level::addBlocks(Blocks b) { blocks.push_back(b); }

void Level::addPlatform(Platform* p) { platforms.push_back(p); }

void Level::addCreature(NPC* npc)
{
    creatures.push_back(npc);
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

std::vector < Creature* > Level::getCreatures()
{
    std::vector < Creature* > rvec;
    for(auto el: creatures)
        rvec.push_back(static_cast < Creature* > (el));
    return rvec;
}

void Level::update(Hero& hero)
{
    for(auto pl: platforms)
        pl->draw();
    for(auto bl: blocks)
        bl.draw(0);
    for(size_t i = 0; i < creatures.size(); i++)
        creatures.at(i)->update(hero, platforms, possible_transitions);
}

#endif
