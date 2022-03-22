
#include "Animation.hpp"
//привет
int main(void)
{
    txCreateWindow(1500,800);
    txSetFillColor(TX_WHITE);
    txClear();
    Animation chroul(0,0,64,64,6,6,960,320,txLoadImage("mainhero.bmp"),TX_WHITE);
    double x = 200;
    double y = 400;
    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        if(GetAsyncKeyState(VK_RIGHT))
        {
            chroul.setY(0);
            x+=10;
        }
        else chroul.set_default_position();
        if(GetAsyncKeyState(VK_LEFT))
        {
            chroul.setY(64);
            x-=10;
        }
        else if(!GetAsyncKeyState(VK_LEFT) && !GetAsyncKeyState(VK_RIGHT)) chroul.set_default_position();
        chroul.update(x,y);

        txSleep(100);
        txClear();
        if(x>=1500+100)
            x = 0-100;
    }
    return 0;
}
