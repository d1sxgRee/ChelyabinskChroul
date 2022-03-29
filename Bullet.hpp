#ifndef __BULLET_HPP__
#define __BULLET_HPP__

#include "AABB.hpp"
#include "Animation.hpp"
#include "Data.hpp"
#include <ctime>

enum class BCondition
{
    InFly,
    None
}

class Bullet
{
private:
    Data data;
    AABB fixture;
    Animation right_animation;
    Animatiom left_animation;
    BCondition bcondition;
    clock_t shot_time;
    double range;  //distance that bullet go

public:
    Bullet(Data, AABB, Animation, Animation, double);
    ~Bullet(){}
    void set_bcondition(BCondition new_bcondition) { bcondition = new_bcondition; }
    Data get_data() { return data; }
    AABB get_fixture() { return fixture; }
    Animation get_animation() { return animation; }
    BCondition get_bcondition() { return bcondition; }
    clock_t get_shot_time() { return shot_time; }
    double get_range() { return range; }
    void shot(Hero &hero, const NPC &npc);

};

Bullet::Bullet(Data _data, AABB _fixture, Animation _right_animation, Animation _left_animation, double _range) :
        data(_data), fixture(_fixture), right_animation(_right_animation), left_animation(_left_animation),
        range(_range), bcondition(BCondition::None){}

void Bullet::shot(Hero &hero, const NPC &npc)
{
    if(bcondition == BCondition::None)
    {
        //устанавливаем координаты
        set_bcondition(BCondition::InFly);
        shot_time = clock();
    }
    if(fixture.collideWithFixture(hero.getFixture(hero.getLastAnimation())))
    {
        switch(npc.direction)
        {
            case Direction::Right:
                hero.setLastAnimation(ATypes::HurtRight);
            case Direction::Left:
                hero.setLastAnimation(ATypes::HurtLeft);
            case Direction::None:
                break;
            default break;
        }
        set_bcondition(BCondition::None);
        return;
    }
    switch(npc.direction)
    {
        case Direction::Right:
            if(npc.getFixture(npc.getLastAnimation()).maximum.x + range <= fixture.maximum.x)
            {
                set_bcondition(BCondition::None);
                return;
            }
            fixture.minimum.x += data.get_velocity_x();
            fixture.maximum.x += data.get_velocity_x();
            right_animation.update(fixture);
            break;
        case Direction::Left:
            if(npc.getFixture(npc.getLastAnimation()).minimum.x - range >= fixture.maximum.x)
            {
                set_bcondition(BCondition::None);
                return;
            }
            fixture.minimum.x -= data.get_velocity_x();
            fixture.maximum.x -= data.get_velocity_x();
            left_animation.update(fixture);
            break;
        case Direction::None:
            break;
        default: break;
    }
}

#endif // __BULLET_HPP__
