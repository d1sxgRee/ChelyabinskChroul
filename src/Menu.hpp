#ifndef __MENU_H__
#define __MENU_H__

class Mouse
{
private:
    int x;
    int y;
    bool lmbclick;
    bool check;
public:
    Mouse();
    void mouseXYCLICK(Mouse* mt);
};

void Mouse::mouseXYCLICK(Mouse* mt)
{
    mt->x = txMouseX();
    mt->y = txMouseY();
    if(GetAsyncKeyState(VK_LBUTTON))
    {
        mt->lmbclick = true;
    }
}

class Menu
{
private:
    double sprite_x;
    double sprite_y;
    double width;
    double height;
    double scaleX;
    double scaleY;
    HDC image;
    COLORREF color;
public:
    Menu(double _x, double _y, double _width, double _height, double _scaleX, double _scaleY, HDC _image,
    COLORREF _color);
    ~Menu();
    void draw(double x,double y);
};
Menu::Menu(double _x, double _y, double _width, double _height, double _scaleX, double _scaleY):
    sprite_x(_x), sprite_y(_y), width(_width), height(_height), scaleX(_scaleX), scaleY(_scaleY),
    image(_image), color(_color)

Menu::~Menu() { txDeleteDC(image); }

Menu::draw(double x, double y)
{
    Win32::TransparentBlt (txDC(), static_cast < int > (x), static_cast < int > (y),
    static_cast < int > (width*scaleX), static_cast < int > (height*scaleY),image,
    static_cast < int > (sprite_x),
    static_cast < int > (sprite_y), static_cast < int > (width),
    static_cast < int > (height), color);
}
#endif //__MENU_H__
