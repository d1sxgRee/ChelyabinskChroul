#include "TXLib.h"
#include "Menu.hpp"

#define WINDOWX 1500
#define WINDOWY 700

int main(void)
{
    txCreateWindow(WINDOWX,WINDOWY);
    txSetFillColor(TX_BLACK);
    txClear();
    Button play({{WINDOWX/2 - 200, WINDOWY/2 - 50}, {WINDOWX/2 + 200,WINDOWY/2 + 50}}, txLoadImage("playbutton.bmp"));
    txBegin();

    while(true)
    {
        play.draw();
        if(play.wasClicked())
            play.getAnimation().setY(619);
        else play.getAnimation().setY(0);
        txSleep(100);
        txClear();
    }
    txEnd();
    return 0;
}


