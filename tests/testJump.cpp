#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <conio.h>

#define DEBUG

const int xv = 12;
const int gravity = 1;

double getMaxJumpHeight(double jump_force)
{
#ifdef DEBUG
    std::cout << "DBGGMJH: " << "jump_force: " << jump_force << std::endl;
    getch();
#endif
    if(jump_force < 2 * gravity)
        return jump_force;
    return jump_force + getMaxJumpHeight(jump_force - gravity);
}

double getJumpWidth(double ydelta, double jump_force)
{
#ifdef DEBUG
    std::cout << "ydelta: " << ydelta << std::endl;
    std::cout << "jump_force: " << jump_force << std::endl;
    getch();
#endif
    if(ydelta < 0)
    {
#ifdef DEBUG
        std::cout << getMaxJumpHeight(jump_force);
#endif
        return xv + getJumpWidth(std::abs(ydelta) + getMaxJumpHeight(jump_force), jump_force - gravity);
    }
    if(ydelta < 2 * jump_force)
        return xv;
    return xv + getJumpWidth(ydelta - jump_force, jump_force - gravity);
}

int main()
{
    std::cout << "0GMJH: " << getMaxJumpHeight(10) << std::endl;
    std::cout << "0GJW: " << getJumpWidth(-20, 20) << std::endl; //broken
    std::cout << "1GMJH: " << getMaxJumpHeight(20) << std::endl;
    std::cout << "1GJW: " << getJumpWidth(20, 10) << std::endl;
}
