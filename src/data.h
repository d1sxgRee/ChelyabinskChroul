#ifndef __DATA_H__
#define __DATA_H__

class Data
{
// variables
private:
    int velocity;
    int health_points;
    int damage;
    double acceleration;
    double slide_cooldown;
    double armour_cooldown;
    double attack_cooldown;

// functions
public:
    // constructor
    Data(int, double, int, double, double, int, double);

    // getters
    int get_velocity();
    int get_health_points();
    int get_damage();
    double get_acceleration();
    double get_armour_cooldown();
    double get_slide_cooldown();
    double get_attack_cooldown();

    // setters
    void set_velocity(int);
    void set_acceleration(double);
    void set_health_points(int);
    void set_damage(int);
    void set_armour_cooldown(double);
    void set_slide_cooldown(double);
    void set_attack_cooldown(double);
};

Data::Data(int _v, double _a, int _hp, double _armour_cd, double _slide_cd, int _dmg, double _attack_cd):
        velocity(_v),  acceleration(_a), health_point(_hp), armour_cooldown(_armour_cd), slide_cooldown(_slide_cd), damage(_dmg), attack_cooldown(_attack_cd) { }

int Data::get_velocity()           { return velocity; }
int Data::get_health_points()      { return health_points; }
int Data::get_damage()             { return damage; }
double Data::get_acceleration()    { return acceleration; }
double Data::get_armour_cooldown() { return armour_cooldown; }
double Data::get_slide_cooldown()  { return slide_cooldown; }
double Data::get_attack_cooldown() { return attack_cooldown; }

void Data::set_velocity(int new_v)                    { velocity = new_v; }
void Data::set_acceleration(double new_a)             { acceleration = new_a; }
void Data::set_health_points(int newhp)               { health_points = newhp; }
void Data::set_damage(int new_dmg)                    { damage = new_dmg; }
void Data::set_armour_cooldown(double new_armour_cd)  { armour_cooldown = new_armour_cd; }
void Data::set_slide_cooldown(double new_slide_cd)    { slide_cooldown = new_slide_cd; }
void Data::set_attack_cooldown (double new_attack_cd) { attack_cooldown = new_attack_cd; }

#endif
