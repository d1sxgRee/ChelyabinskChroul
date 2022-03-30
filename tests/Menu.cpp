#include "TXLib.h"
#include "Menu.hpp"

#define WINDOWX 1500
#define WINDOWY 700

int main(void)
{
    txCreateWindow(WINDOWX,WINDOWY);
    txSetFillColor(TX_BLACK);
    txClear();
    Menu buttons( Button({{WINDOWX/2 - 200, WINDOWY/2 - 50}, {WINDOWX/2 + 200,WINDOWY/2 + 50}},
    619, Animation(0, 0, 1075, 609, 1.0, 1.0, 0, 0, txLoadImage("playbutton.bmp"), TX_WHITE)),
    Button({{1300, 10},{1400, 110}}, 577, Animation(0, 0, 613, 533, 1.0, 1.0, 0, 0, txLoadImage("infobutton.bmp"), TX_WHITE)));
    //txBegin();
    while(2==2)
    {
        buttons.draw();
        //buttons.update();
        txSleep(100);
        txClear();
    }
    //txEnd();
    return 0;
}


