#include <iostream>

const int xv = 12;
const int gravity = 1;

double getMaxJumpHeight(double jump_force)
{
    if(jump_force < 2 * gravity)
        return jump_force;
    return jump_force + getMaxJumpHeight(jump_force - gravity);
}

double getJumpWidth(double ydelta, double jump_force)
{
    if(ydelta < 2 * jump_force)
        return xv;
    return xv + getJumpWidth(ydelta - jump_force, jump_force - gravity);
}

int main()
{
    std::cout << getMaxJumpHeight(20) << std::endl;
    std::cout << getJumpWidth(20, 10) << std::endl;
}
