#ifndef __NPC_H__
#define __NPC_H__

#include "Creature.hpp"
#include "Hero.hpp"

struct Circle { Coords center; double radius; };

enum class Command
{
    StayLeft,
    StayRight,
    StepRight,
    StepLeft,
    AttackRight,
    AttackLeft,
    JumpNone,
    JumpLeft,
    JumpRight,
    SlideRight,
    SlideLeft
};

enum class State
{
    Patrooling,
    Attacking,
    Fleeing,
    Idling,
    FullApathy,
    Searching
};

class NPC : public Creature
{
private:
    Circle interaction_circle;
    State npc_state;
    bool hero_visibility;

    std::map < State, std::vector < Command > > pallete;
public:
    NPC(std::map < ATypes, std::pair < Animation, AABB > >, Data, Direction, Condition, Circle);
    void addCommands(std::vector < Platform* >, std::vector < std::vector < size_t > >);
    void update(std::vector < Platform* >, std::vector < std::vector < size_t > >);
};

NPC::NPC(std::map < ATypes, std::pair < Animation, AABB > > _animations, Data _data,
         Direction _direction, Condition _condition, Circle _interaction_circle) :
    Creature(_animations, _data, _direction, _condition), interaction_circle(_interaction_circle),
    npc_state(State::Idling), hero_visibility(false), pallete()
{
}

void NPC::addCommands(std::vector < Platform* > platforms, std::vector < std::vector < size_t > > possible_transitions)
{
    int this_platform_number = -1;
    for(size_t i = 0; i < platforms.size(); i++)
    {
        if(animations.at(last_animation).second.collideWithFixture(platforms.at(i)->get_fixture()))
            this_platform_number = i;
    }

    if(this_platform_number == -1)
        condition == Condition::FreeFall;

    if(npc_state == State::Patrooling)
    {
        size_t postrans_num = possible_transitions.at(this_platform_number).size();
        if(postrans_num == 0)
            npc_state = State::Idling;
        else
        {
            size_t rndpl = possible_transitions.at(this_platform_number).at(rand() % postrans_num);
            if( platforms.at(this_platform_number)->get_fixture().minimum.x < platforms.at(rndpl)->get_fixture().minimum.x &&
                platforms.at(this_platform_number)->get_fixture().maximum.x < platforms.at(rndpl)->get_fixture().maximum.x )
            {
                if( platforms.at(this_platform_number)->get_fixture().minimum.x + data.get_velocity_x() >
                    platforms.at(this_platform_number)->get_fixture().minimum.x )
                {
                    pallete.at(State::Patrooling).push_back(Command::StepLeft);
                }
                else if( platforms.at(this_platform_number)->get_fixture().minimum.x + data.get_velocity_x() > animations.at(last_animation).second.minimum.x)
                {
                    pallete.at(State::Patrooling).push_back(Command::JumpRight);
                }
                else pallete.at(State::Patrooling).push_back(Command::StayLeft);

            }
            else if(platforms.at(this_platform_number)->get_fixture().maximum.x > platforms.at(rndpl)->get_fixture().maximum.x &&
                    platforms.at(this_platform_number)->get_fixture().minimum.x > platforms.at(rndpl)->get_fixture().minimum.x)
            {
                if( platforms.at(this_platform_number)->get_fixture().maximum.x - data.get_velocity_x() >
                    platforms.at(this_platform_number)->get_fixture().maximum.x )
                {
                    pallete.at(State::Patrooling).push_back(Command::StepRight);
                }
                else if( platforms.at(this_platform_number)->get_fixture().maximum.x - data.get_velocity_x() > animations.at(last_animation).second.maximum.x)
                {
                    pallete.at(State::Patrooling).push_back(Command::JumpLeft);
                }
                else
                    pallete.at(State::Patrooling).push_back(Command::StayRight);
            }
            else
            {
                pallete.at(State::Patrooling).push_back(Command::JumpNone);
            }

        }


    }
    else if(npc_state == State::Idling)
    {
        size_t rndcommand = rand()%12;
        if(platforms.at(this_platform_number)->get_fixture().maximum.x - data.get_velocity_x() > animations.at(last_animation).second.maximum.x &&
        (rndcommand == 0 || rndcommand == 1 || rndcommand == 2))
            pallete.at(State::Idling).push_back(Command::StepRight);
        else if(platforms.at(this_platform_number)->get_fixture().minimum.x + data.get_velocity_x() < animations.at(last_animation).second.minimum.x &&
        (rndcommand == 3 || rndcommand == 4 || rndcommand == 5))
            pallete.at(State::Idling).push_back(Command::StepLeft);
        else if(rndcommand == 6)
            pallete.at(State::Idling).push_back(Command::JumpNone);
        else
            pallete.at(State::Idling).push_back(Command::StayRight);
    }
    else if(npc_state == State::FullApathy)
    {
        size_t rndcommand = rand() % 10;
        if(rndcommand < 5)
            pallete.at(State::FullApathy).push_back(Command::StayRight);
        else if(rndcommand == 6)
        {
            pallete.at(State::FullApathy).push_back(Command::StepRight);
            pallete.at(State::FullApathy).push_back(Command::StepLeft);
        }
        else if(rndcommand == 7)
        {
            pallete.at(State::FullApathy).push_back(Command::StepLeft);
            pallete.at(State::FullApathy).push_back(Command::StepRight);
        }
        else
            pallete.at(State::FullApathy).push_back(Command::StayLeft);
    }
}

void NPC::update(std::vector < Platform* > platforms, std::vector < std::vector < size_t > > possible_transitions)
{
    clock_t start = clock();
    addCommands(platforms, possible_transitions);
    for(auto el: pallete)
    {
        if(el.first == npc_state)
        {
            for(auto command: el.second)
            {
                if(command == Command::StayRight)
                {
                    animations.at(ATypes::StayRight).first.update(animations.at(ATypes::StayRight).second);
                }
                else if(command == Command::StayLeft)
                {
                    animations.at(ATypes::StayLeft).first.update(animations.at(ATypes::StayLeft).second);
                }
                else if(command == Command::StepRight && condition == Condition::OnPlatform)
                {
                    setDirection(Direction::Right);
                    go(true);
                }
                else if(command == Command::StepLeft && condition == Condition::OnPlatform)
                {
                    setDirection(Direction::Left);
                    go(true);
                }
                else if(command == Command::AttackRight && condition == Condition::OnPlatform)
                {
                }
                else if(command == Command::AttackLeft && condition == Condition::OnPlatform)
                {
                }
                else if(command == Command::JumpRight || (condition != Condition::OnPlatform && direction == Direction::Right))
                {
                    setDirection(Direction::Right);
                    jump(NPC_JUMP_FORCE);
                }
                else if(command == Command::JumpLeft || (condition != Condition::OnPlatform && direction == Direction::Left))
                {
                    setDirection(Direction::Left);
                    jump(NPC_JUMP_FORCE);
                }
                else if(command == Command::JumpNone || (condition != Condition::OnPlatform && direction == Direction::None))
                {
                    setDirection(Direction::None);
                    jump(NPC_JUMP_FORCE);
                }
                else if(command == Command::SlideRight || slide_state == Sliding::InSlide)
                {
                    slide();
                }
                else if(command == Command::StayRight)
                {
                    animations.at(ATypes::StayRight).first.update(animations.at(ATypes::StayRight).second);
                    setLastAnimation(ATypes::StayRight);
                }
                else if(command == Command::StayLeft)
                {
                    animations.at(ATypes::StayLeft).first.update(animations.at(ATypes::StayRight).second);
                    setLastAnimation(ATypes::StayLeft);
                }
                updateAllFixtures();
                updateCondition(platforms);
            }
        }

    }
}


#endif //__NPC_H__
