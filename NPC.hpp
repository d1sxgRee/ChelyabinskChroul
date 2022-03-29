#ifndef __NPC_H__
#define __NPC_H__

#include "Creature.hpp"
#include "Hero.hpp"

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

enum class NPC_type
{
    Brawler,
    Sniper
}

class NPC : public Creature
{
private:
    Bullet bullet;
    Circle interaction_circle;
    State npc_state;
    NPC_type npc_type;
    bool hero_visibility;

    std::map < State, std::vector < Command > > pallete;
public:
    NPC (std::map < ATypes, std::pair < Animation, AABB > >, Data, Direction, Condition, Bullet, Circle, NPC_type);
    void updateState(Hero& hero);
    void addCommands (Hero&, std::vector < Platform* >, std::vector < std::vector < size_t > >);
    void update (Hero&, std::vector < Platform* >, std::vector < std::vector < size_t > >);
};

NPC::NPC (std::map < ATypes, std::pair < Animation, AABB > > _animations, Data _data,
          Direction _direction, Condition _condition, Bullet _bullet, Circle _interaction_circle, NPC_type _npc_type) :
    Creature (_animations, _data, _direction, _condition), bullet(_bullet), interaction_circle (_interaction_circle),
    npc_type(_npc_type), npc_state (State::Idling), hero_visibility (false), pallete()
{
}

void NPC::updateState(Hero& hero)
{
    if(hero.getFixture(Hero.getLastAnimation()).collideWithFCircle(interaction_circle))
    {
        if(hero_visibility)
        {
            if(data.get_health_points() > NPC_MAX_HP * 0.2)
                npc_state = State::Attacking;
            else
                npc_state = State::Fleeing;
        }
        else
            npc_state = State::Searching;
    }
    else
    {
        if(data.get_health_points() > NPC_MAX_HP * 0.5)
            npc_state = State::Patrooling;
        else if(data.get_health_points() > NPC_MAX_HP * 0.2)
            npc_state = State::Idling;
        else
            npc_state = State::FullApathy;
    }
}

void NPC::addCommands (Hero& hero, std::vector < Platform* > platforms, std::vector < std::vector < size_t > > possible_transitions)
{
    int this_platform_number = -1;

    for (size_t i = 0; i < platforms.size(); i++)
    {
        if (animations.at (last_animation).second.collideWithFixture (platforms.at (i)->get_fixture()))
            this_platform_number = i;
    }

    if (this_platform_number == -1)
    {
        condition == Condition::FreeFall;
        return;
    }

    size_t postrans_num = possible_transitions.at(this_platform_number).size();

    double this_maxxcrd = platforms.at(this_platform_number)->get_fixture().maximum.x;
    double this_minxcrd = platforms.at(this_platform_number)->get_fixture().minimum.x;
    size_t rndpl = possible_transitions.at(this_platform_number).at(rand() % postrans_num);
    double rndpl_maxxcrd = platforms.at(rndpl)->get_fixture().maximum.x;
    double rndpl_minxcrd = platforms.at(rndpl)->get_fixture().minimum.x;

    if (npc_state == State::Patrooling)
    {
        if (postrans_num == 0)
            npc_state = State::Idling;
        else
        {
            if (rndpl_maxxcrd <= this_minxcrd)
            {
                if (this_minxcrd > animations.at (last_animation).second.minimum.x - data.get_velocity_x())
                    pallete.at (State::Patrooling).push_back (Command::StepLeft);
                else
                    pallete.at (State::Patrooling).push_back (Command::JumpLeft);
            }
            else if (rndpl_minxcrd >= this_maxxcrd)
            {
                if (this_maxxcrd > animations.at (last_animation).second.maximum.x + data.get_velocity_x())
                    pallete.at (State::Patrooling).push_back (Command::StepRight);
                else
                    pallete.at (State::Patrooling).push_back (Command::JumpRight);

            }
            else if (rndpl_minxcrd <= this_minxcrd && rndpl_maxxcrd <= this_maxxcrd)
            {
                pallete.at (State::Patrooling).push_back (Command::JumpNone);
            }
            else if (rndpl_minxcrd >= this_minxcrd && rndpl_maxxcrd <= this_maxxcrd)
            {
                double maxxdelta = std::abs (rndpl_maxxcrd - this_maxxcrd);
                double minxdelta = std::abs (rndpl_minxcrd - this_minxcrd);

                if (minxdelta > data.get_velocity_x() && maxxdelta > data.get_velocity_x())
                {
                    if (maxxdelta < minxdelta)
                    {
                        if (this_maxxcrd - data.get_velocity_x() > animations.at (last_animation).second.maximum.x)
                            pallete.at (State::Patrooling).push_back (Command::StepRight);
                        else
                            pallete.at (State::Patrooling).push_back (Command::JumpLeft);
                    }
                    else if (maxxdelta > minxdelta)
                    {
                        if (this_minxcrd + data.get_velocity_x() < animations.at (last_animation).second.minimum.x)
                            pallete.at (State::Patrooling).push_back (Command::StepLeft);
                        else
                            pallete.at (State::Patrooling).push_back (Command::JumpLeft);
                    }
                    else
                        pallete.at (State::Patrooling).push_back (Command::JumpNone);
                }
            }

        }


    }

    else if(npc_state == State::Attacking)
    {
    }

    else if(npc_state == State::Fleeing)
    {
    }

    else if (npc_state == State::Idling)
    {
        size_t rndcommand = rand() % 12;

        if (this_maxxcrd - data.get_velocity_x() > animations.at (last_animation).second.maximum.x &&
                (rndcommand == 0 || rndcommand == 1 || rndcommand == 2))
            pallete.at (State::Idling).push_back (Command::StepRight);
        else if (this_minxcrd + data.get_velocity_x() < animations.at (last_animation).second.minimum.x &&
                 (rndcommand == 3 || rndcommand == 4 || rndcommand == 5))
            pallete.at (State::Idling).push_back (Command::StepLeft);
        else if (rndcommand == 6)
            pallete.at (State::Idling).push_back (Command::JumpNone);
        else
            pallete.at (State::Idling).push_back (Command::StayRight);
    }

    else if (npc_state == State::FullApathy)
    {
        size_t rndcommand = rand() % 10;

        if (rndcommand < 5)
            pallete.at (State::FullApathy).push_back (Command::StayRight);
        else if (rndcommand == 6)
        {
            pallete.at (State::FullApathy).push_back (Command::StepRight);
            pallete.at (State::FullApathy).push_back (Command::StepLeft);
        }
        else if (rndcommand == 7)
        {
            pallete.at (State::FullApathy).push_back (Command::StepLeft);
            pallete.at (State::FullApathy).push_back (Command::StepRight);
        }
        else
            pallete.at (State::FullApathy).push_back (Command::StayLeft);
    }

    else if(npc_state == State::Searching)
    {
    }

}

void NPC::update (Hero& hero, std::vector < Platform* > platforms, std::vector < std::vector < size_t > > possible_transitions)
{
    static size_t it = 0;
    clock_t start = clock();
    State last_state = npc_state;
    updateState (hero);
    if(last_state != npc_state)
        it = 0;
    addCommands (hero, platforms, possible_transitions);

    Command command = pallete.at(npc_state).at(it);
    if (command == Command::StayRight)
    {
        animations.at (ATypes::StayRight).first.update (animations.at (ATypes::StayRight).second);
    }
    else if (command == Command::StayLeft)
    {
        animations.at (ATypes::StayLeft).first.update (animations.at (ATypes::StayLeft).second);
    }
    else if (command == Command::StepRight && condition == Condition::OnPlatform)
    {
        setDirection (Direction::Right);
        go (true);
    }
    else if (command == Command::StepLeft && condition == Condition::OnPlatform)
    {
        setDirection (Direction::Left);
        go (true);
    }
    else if (command == Command::AttackRight && condition == Condition::OnPlatform && npc_type == NPC_type::Brawler)
    {

    }
    else if (command == Command::AttackLeft && condition == Condition::OnPlatform && npc_type == NPC_type::Brawler)
    {
    }
    else if ((command == Command::AttackRight && condition == Condition::OnPlatform && npc_type == NPC_type::Sniper &&
    (clock() - bullet.shot_time) / CLOCKS_PER_SEC >= bullet.data.attack_cooldown) || bullet.bcondition == BCondition::InFly )
    {
        bullet.shot(hero, *this);
    }
    else if ((command == Command::AttackLeft && condition == Condition::OnPlatform && npc_type == NPC_type::Sniper &&
    (clock() - bullet.shot_time) / CLOCKS_PER_SEC >= bullet.data.attack_cooldown) || bullet.bcondition == BCondition::InFly )
    {
        bullet.shot(hero, *this);
    }
    else if (command == Command::JumpRight || (condition != Condition::OnPlatform && direction == Direction::Right))
    {
        setDirection (Direction::Right);
        jump (NPC_JUMP_FORCE);
    }
    else if (command == Command::JumpLeft || (condition != Condition::OnPlatform && direction == Direction::Left))
    {
        setDirection (Direction::Left);
        jump (NPC_JUMP_FORCE);
    }
    else if (command == Command::JumpNone || (condition != Condition::OnPlatform && direction == Direction::None))
    {
        setDirection (Direction::None);
        jump (NPC_JUMP_FORCE);
    }
    else if (command == Command::SlideRight || (condition == Condition::OnPlatform &&
             slide_state == Sliding::InSlide && direction == Direction::Right))
    {
        setDirection (Direction::Right);
        slide();
    }
    else if (command == Command::SlideLeft || (condition == Condition::OnPlatform &&
             slide_state == Sliding::InSlide && direction == Direction::Right))
    {
        setDirection (Direction::Left);
        slide();
    }

    updateAllFixtures();
    updateCondition (platforms);
    it++;
}


#endif //__NPC_H__
