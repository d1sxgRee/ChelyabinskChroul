#ifndef __GLOBALS_H__
#define __GLOBALS_H__

const double gravity = 9.81;

const int RKEY = int('D');                              /*The button responsible for moving to the right*/
const int LKEY = int('A');                              /*the button responsible for moving to the left*/
const int JUMP = int(VK_SPACE);                         /*The button responsible for jumping*/
const int AKEY = int(VK_LBUTTON);                       /*The button responsible for attack*/

const unsigned short WindowX = 1500;                /*Window OX axis length*/
const unsigned short WindowY = 700;                 /*Window OY axis length*/
const unsigned short WindowR = WindowX / WindowY;   /*Window OX / OY lengths ratio*/

#endif //__GLOBALS_H__
