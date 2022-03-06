#ifndef __BLOCKS_HPP__
#define __BLOCKS_HPP__

#include "TXLib.h"
#include <cassert>

class Blocks
{
private:
    double paint_y;
    double size_x;
    double size_y;
    double width;
    double height;
    HDC background_image;
    double x_screen;
    double y_screen;
public:
    // constructor
    Blocks( double, double, double, double, double, HDC, double, double );
    // destructor
    ~Blocks();
    // drawing
    void background_draw(int);
};
Blocks::Blocks( double _paint_y, double _size_x, double _size_y, double _width, double _height, HDC _background_image, double _x_screen, double _y_screen):
    paint_y(_paint_y), size_x(_size_x), size_y(_size_y), width(_width), height(_height), background_image(_background_image), x_screen(_x_screen), y_screen(_y_screen)
{
    assert(background_image != nullptr);
    assert(size_x >= 0);
    assert(size_y >= 0);
    assert(width >= 0);
    assert(height >= 0);
}

Blocks::~Blocks()
{
    txDeleteDC(background_image);
}

void Blocks::background_draw(int i)
{
    assert(i >= 0);
    Win32::TransparentBlt( txDC(), static_cast<int>(x_screen), static_cast<int>(y_screen),
    static_cast<int>(size_x), static_cast<int>(size_y), background_image, static_cast<int>(i * size_x),
    static_cast<int>(paint_y), static_cast<int>(width), static_cast<int>(height), TX_BLACK);
}
#endif //__BLOCKS_HPP__
