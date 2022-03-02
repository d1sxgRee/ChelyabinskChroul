
/* класс который знает про спрайтшит и размер одного спрайта...
    проходится и рисует
    в принципе все
*/
#ifndef __ANIMATION_HPP__
#define __ANIMATION_HPP__
#include <TXLib.h>

class Animation
{
private:
    double sprite_x; //коориднаты захвата на спрайтшите
    double sprite_y; //тоже самое только по у
    double width;    //ширина спрайта
    double height;   //высота спрайта
    double scaleX;   //требуемое изменение картинки на холсте по ох
    double scaleY;   //требуемое изменение картинки на холсте по оу
    double endX;     //конечная длина одного спрайтшита
    HDC image;       //указатель на спрайтшит
    COLORREF color;  //удаляемый цвет со спрайта
public:
    Animation(double _x, double _y, double _width, double _height, double _scaleX, double _scaleY, double _endX, HDC _image, COLORREF _color);
    Animation(const Animation& a);
    Animation& operator= (const Animation& a);
    ~Animation();
    void draw(double x,double y);
    void update(double x, double y);
    void setY(double y);
};

Animation::Animation(double _x, double _y, double _width, double _height, double _scaleX, double _scaleY, double _endX, HDC _image, COLORREF _color):
    sprite_x(_x), sprite_y(_y), width(_width), height(_height), scaleX(_scaleX), scaleY(_scaleY), endX(_endX),
    image(_image), color(_color)
{
    if(image==nullptr)
    {
        txMessageBox("Не найден файл со спрайтом", "Ошибка");
        exit(0);
    }
}

Animation::Animation(const Animation& a) :
    sprite_x(a.sprite_x), sprite_y(a.sprite_y), width(a.width), height(a.height), scaleX(a.scaleX),
    scaleY(a.scaleY), endX(a.endX), image(a.image), color(a.color) {}

Animation::~Animation() { txDeleteDC(image); }

void Animation::draw(double x, double y)
{
    Win32::TransparentBlt (txDC(), static_cast < int > (x), static_cast < int > (y),
    static_cast < int > (width*scaleX), static_cast < int > (height*scaleY),
    image, static_cast < int > (sprite_x),
    static_cast < int > (sprite_y), static_cast < int > (width),
    static_cast < int > (height), color);
}



void Animation::update(double screen_x, double screen_y)
{
    draw(screen_x, screen_y);
    sprite_x+= width;
    if(sprite_x >= endX-width)
    {
        sprite_x = 1;
    }
}

void Animation::setY(double y){sprite_y=y;}

#endif //__ANIMATION_H__

