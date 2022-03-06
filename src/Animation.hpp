#ifndef __ANIMATION_HPP__
#define __ANIMATION_HPP__

#include "TXLib.h"

const int start_x = 1;

class Animation
{
private:
    double sprite_x; //���������� ������� �� ����������
    double sprite_y; //���� ����� ������ �� �
    double width;    //������ �������
    double height;   //������ �������
    double scaleX;   //��������� ��������� �������� �� ������ �� ��
    double scaleY;   //��������� ��������� �������� �� ������ �� ��
    double endX;     //�������� ����� ������ ����������
    double loop_x;   //������� ������ ����� �� ������� �� �
    HDC image;       //��������� �� ���������
    COLORREF color;  //��������� ���� �� �������
public:
    Animation(double _x, double _y, double _width, double _height, double _scaleX, double _scaleY, double _endX, double _loop_x, HDC _image, COLORREF _color);
    Animation(const Animation& a);
    Animation& operator= (const Animation& a) = default;
    ~Animation();
    void draw(double x,double y);
    void update(double x, double y);
    void setY(double y);
    void set_default_position();
};

Animation::Animation(double _x, double _y, double _width, double _height, double _scaleX, double _scaleY, double _endX, double _loop_x, HDC _image, COLORREF _color):
    sprite_x(_x), sprite_y(_y), width(_width), height(_height), scaleX(_scaleX), scaleY(_scaleY), endX(_endX), loop_x(_loop_x),
    image(_image), color(_color)
{
    assert(image != nullptr);
    assert(width >= 0);
    assert(height >= 0);
    assert((loop_x >= 0) && (loop_x <= endX));

}

Animation::Animation(const Animation& a) :
    sprite_x(a.sprite_x), sprite_y(a.sprite_y), width(a.width), height(a.height), scaleX(a.scaleX),
    scaleY(a.scaleY), endX(a.endX),loop_x(a.loop_x), color(a.color)
{
    image = txCreateCompatibleDC(a.endX, a.height);
    txBitBlt(image, 0, 0, 0, 0, a.image);
}

Animation::~Animation() { txDeleteDC(image); }

void Animation::draw(double x, double y)
{
    Win32::TransparentBlt (txDC(), static_cast < int > (x), static_cast < int > (y),
    static_cast < int > (width*scaleX), static_cast < int > (height*scaleY),image,
    static_cast < int > (sprite_x),
    static_cast < int > (sprite_y), static_cast < int > (width),
    static_cast < int > (height), color);
}



void Animation::update(double screen_x, double screen_y)
{
    draw(screen_x, screen_y);
    sprite_x += width;
    if(sprite_x > endX-width)
    {
        sprite_x = loop_x;
    }
}

void Animation::setY(double y)
{
    sprite_y = y;
}

void Animation::set_default_position()
{
    sprite_x = start_x;
}

#endif //__ANIMATION_H__
