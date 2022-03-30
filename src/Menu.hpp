#ifndef __MENU_H__
#define __MENU_H__

#include "AABB.hpp"
#include "Animation.hpp"

class Button
{
private:
    AABB fixture;
    int new_y;
    Animation button;
public:
    Button(AABB, int, Animation);
    ~Button() = default;
    bool pushed();
    void draw();
    void update();
};

Button::Button(AABB _fixture, int _new_y, Animation _button):
    fixture(_fixture), new_y(_new_y), button(_button) {}

bool Button::pushed()
{
    if(fixture.minimum.x < txMouseX() && fixture.maximum.x > txMouseX())
        if(fixture.minimum.y < txMouseY() && fixture.maximum.y > txMouseY())
            if(GetAsyncKeyState(VK_LBUTTON))
                return true;
    return false;
}

void Button::draw()
{
    button.draw(fixture);
}

void Button::update()
{
    if(pushed())
        button.setY(new_y);
    else button.setY(0);
}

///-----------------------------------------

class Menu
{
private:
    Button play;
    Button info;
    //Button exit;
public:
    Menu(Button, Button);
    ~Menu() {};
    void draw();
    void update();
};

Menu::Menu(Button _play, Button _info):
    play(_play), info(_info) {}

void Menu::draw()
{
    play.draw();
    info.draw();
    //exit.draw();
}

void Menu::update()
{
    play.update();
    info.update();
    //exit.update();
}
#endif //__MENU_H__
