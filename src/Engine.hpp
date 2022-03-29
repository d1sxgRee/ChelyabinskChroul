#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "Level.hpp"
#include "Hero.hpp"
#include "NPC.hpp"

class Engine
{
private:
    Level level;
    Hero hero;
public:
    Engine(Level _level, Hero _hero);
    ~Engine() = default;
    void start(int exit_key, int ms_sleep_time);
    std::vector <Creature*> get_visible_npcs();
};

Engine::Engine(Level _level, Hero _hero) :
    level(_level), hero(_hero) {}

void Engine::start(int exit_key, int ms_sleep_time)
{
    txBegin();
    while(!GetAsyncKeyState(exit_key))
    {
        pause_if(PKEY);
        level.update(hero);
        hero.update(level.getPlatforms(), level.getCreatures());
        screen_update(ms_sleep_time);
    }
    txEnd();
}

std::vector <Creature*> Engine::get_visible_npcs()
{
    std::vector <Creature*> tmp;
    for(auto c: level.getCreatures())
    {
        if (level.visioble(hero.getCoords(), c->getCoords()))
        {
            tmp.push_back(c);
        }
    }
    return tmp;
}

#endif //__ENGINE_H__
