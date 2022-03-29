#ifndef __MENU_H__
#define __MENU_H__

#include "AABB.hpp"
#include "Animation.hpp"

class Button
{
private:
    AABB fixture;
    HDC play_image;
    Animation one;
public:

    Button(AABB,HDC);
    ~Button();
    bool wasClicked();
    void draw();
    Animation& getAnimation();
};

Button::Button(AABB _fixture, HDC _play_image):
    fixture(_fixture), play_image(_play_image),one(0, 0, 1075, 609, 1.0, 1.0, 0, 0,
    play_image, TX_WHITE) {}

Button::~Button()
{
    txDeleteDC(play_image);
}

bool Button::wasClicked()
{
    if(fixture.minimum.x < txMouseX() && fixture.maximum.x > txMouseX())
        if(fixture.minimum.y < txMouseY() && fixture.maximum.y > txMouseY())
            if(GetAsyncKeyState(VK_LBUTTON))
                return true;
    else return false;
}

void Button::draw()
{
    one.draw(fixture);
}

Animation& Button::getAnimation() { return one; }

#endif //__MENU_H__
