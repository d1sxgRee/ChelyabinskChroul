#ifndef __BULLET_HPP__
#define __BULLET_HPP__

#include "AABB.hpp"
#include "Animation.hpp"
#include "Data.hpp"
#include "hero.hpp"
#include <ctime>

enum class BCondition
{
    InFly,
    None
};

class Bullet
{
private:
    Data data;
    AABB fixture;
    Animation right_animation;
    Animation left_animation;
    BCondition bcondition;
    clock_t shot_time;
    double range;  //distance that bullet go

public:
    Bullet(Data, AABB, Animation, Animation, double);
    ~Bullet(){}
    void set_bcondition(BCondition new_bcondition) { bcondition = new_bcondition; }
    Data get_data() { return data; }
    AABB get_fixture() { return fixture; }
    Animation get_right_animation() { return right_animation; }
    Animation get_left_animation() { return left_animation; }
    BCondition get_bcondition() { return bcondition; }
    clock_t get_shot_time() { return shot_time; }
    double get_range() { return range; }
    void shot(Hero &hero, double min_x, double max_x, Direction direction);

};

Bullet::Bullet(Data _data, AABB _fixture, Animation _right_animation, Animation _left_animation, double _range) :
        data(_data), fixture(_fixture), right_animation(_right_animation), left_animation(_left_animation),
        bcondition(BCondition::None), shot_time(0), range(_range){}

void Bullet::shot(Hero &hero, double min_x, double max_x, Direction direction)
{
    if(bcondition == BCondition::None)
    {
        //устанавливаем координаты
        set_bcondition(BCondition::InFly);
        shot_time = clock();
    }
    if(fixture.collideWithFixture(hero.getFixture(hero.getLastAnimation())))
    {
        if(direction == Direction::Right)
        {
            hero.setLastAnimation(ATypes::HurtRight);
        }
        else if(direction == Direction::Left)
        {
            hero.setLastAnimation(ATypes::HurtLeft);
        }
        else
            set_bcondition(BCondition::None);
        return;
    }
    if(direction == Direction::Right)
    {
        if(max_x + range <= fixture.maximum.x)
        {
            set_bcondition(BCondition::None);
            return;
        }
        fixture.minimum.x += data.get_velocity_x();
        fixture.maximum.x += data.get_velocity_x();
        right_animation.update(fixture);
    }
    else if(direction == Direction::Left)
    {
        if(min_x - range >= fixture.maximum.x)
        {
            set_bcondition(BCondition::None);
            return;
        }
        fixture.minimum.x -= data.get_velocity_x();
        fixture.maximum.x -= data.get_velocity_x();
        left_animation.update(fixture);
    }
}

#endif // __BULLET_HPP__
