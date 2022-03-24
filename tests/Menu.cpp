#include "TXLib.h"
#include "Menu.hpp"

int main(void)
{
    txCreateWindow(1500,700);
    txSetFillColor(TX_BLACK);
    txClear();
    // HDC background = txLoadImage("...");
    HDC play_off = txLoadImage("playbutton.bmp");
    HDC play_on = txLoadImage("pushed_playbutton.bmp");
    Mouse mouse();


    return 0;
}


