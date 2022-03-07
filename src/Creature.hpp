#ifndef __CREATURE_H__
#define __CREATURE_H__

#include "Coords.hpp"
#include "Globals.hpp"
#include "AABB.hpp"
#include "Animation.hpp"
#include "Data.hpp"
#include "Level.hpp"
#include <map>
#include <fstream>
#include <cassert>

enum Command
{
    GRIGHT,
    GLEFT,
    JUMP,
    ATTACK
};

static std::map < std::string, E > const commandTable =
    {{"GRIGHT", Command::GRIGHT},
     {"GLEFT", Command::GLEFT},
     {"JUMP", Command::JUMP},
     {"ATTACK", Command::ATTACK}};

class Creature
{
private:
    Coords coords;
    Data data;
    std::map < Command, Animation > animations;
public:
    Creature(Coords _coords, Data _data, std::map < Command, Animation > _animations);
    initAnimations(std::string path);

    void addAnimation(Command command, Animation animation);
    int executeCommand(Command command); // возвращает 1, если дана некоректная комманда
    void moveRight();
    void moveLeft();
    void jump();
    void keys_interaction(int rkey, int lkey) = delete;
    Coords getCoords();
    Data getData();
};

Creature::Creature(Coords _coords, Data _data, std::map < std::string, Animation > _animations) :
    coords(_coords), data(_data), animations(_animations) {}

void Creature::addAnimation(Command command, Animation animation)
{
    if(animations.count(command) != 0)
        return;
    animations.insert(std::make_pair(command, animation));
}

Creature::initAnimations(std::string path)
{
    fistream fin (path);
    std::string buffer;
    fin >> buffer;

}

void Creature:::executeCommand(Command command)
{
    assert(animations.contains(command));
    switch (command){
      case GRIGHT:
          this->moveRight();
          break();
      case GLEFT:
          this->moveLeft();
          break();
      case JUMP:
          this->jump();
          break();
      case ATTACK:
          break();
    }
}

void Creature::moveRight()
{
    coords.x += std::abs(data.get_velocity());
    coords.y += std::abs(data.get_velocity()) / WindowR;
    data.set_velocity(std::abs(data.get_velocity()) + std::abs(data.get_acceleration()));
}

void Creature::moveLeft()
{
    coords.x -= std::abs(data.get_velocity());
    coords.y -= std::abs(data.get_velocity()) / WindowR;
    data.set_velocity(std::abs(data.get_velocity()) + std::abs(data.get_acceleration()));
}

void Creature::jump(Level level)
{
    /*Please create creature jump!*/
}

Coords Creature::getCoords() { return coords; }
Data Creature::getData() { return data; }

#endif //__CREATURE_H__
