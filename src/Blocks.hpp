#include <TXLib.h>
#ifndef __BLOCKS_HPP__
#define __BLOCKS_HPP__
class Blocks
{
private:
    double paint_y;
    double size_x;
    double size_y;
    double width;
    double high;
    HDC background_image;
    double x_screen;
    double y_screen;
public:
    // constructor
    Blocks( double, double, double, double, double, HDC, double, double );

    // drawing
    void background_draw(int);

};
Blocks::Blocks( double _paint_y, double _size_x, double _size_y, double _width, double _high, HDC _background_image, double _x_screen, double _y_screen):
    paint_x(_paint_x), paint_y(_paint_y),size_x(_size_x), size_y(_size_y), width(_width), hugh(_high), background_image(_background_image), x_screen(_x_screen), y_screen(_y_screen) { }

Blocks::background_draw(int i)
{
    Win32::TransparentBlt( txDC(), x_screen, y_screen, size_x, size_y, background_image, double(i)*size_x, paint_y, width, high )
}
#endif //__BLOCKS_HPP__
