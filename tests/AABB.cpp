#include <iostream>
#include <vector>
#include "AABB.hpp"

#define PRINT_RESULTS

int main()
{
    Coords circle_center = {200, 200};
    double radius = 20;
    AABB a = {{100, 100}, {200, 200}};
    AABB b = {{150, 150}, {250, 250}};
    a = b;
#ifdef PRINT_RESULTS
    std::cout << a.minimum.x << " " << a.minimum.y << std::endl;
    std::cout << a.maximum.x << " " << a.maximum.y << std::endl;
#endif
    if(a.minimum.x == b.minimum.x && a.maximum.x == b.maximum.x &&
        a.minimum.y == b.minimum.y && a.maximum.y == b.maximum.y)
        std::cout << "Copy constructor works correctly" << std::endl;
    bool result = a.collideWithFixture(b);
#ifdef PRINT_RESULTS
    std::cout << result << std::endl;
#endif
        std::vector <AABB> v = {{{110, 110}, {900, 900}}, {{60, 60}, {120, 120}}, {{150, 150}, {170, 170}}, {{300, 300}, {350, 350}}, {{11, 11}, {12, 12}}};
        std::vector <bool> tv = {true, false, true, false, false};
        std::vector <bool> ov;
        for(size_t i = 0; i < v.size(); i++)
        {
            bool result = a.collideWithFixture(v.at(i));
#ifdef PRINT_RESULTS
            std::cout << result << std::endl;
#endif
            ov.push_back(result);
        }
        bool True = true;
        for(size_t i = 0; i < ov.size(); i++)
        {
            if(ov.at(i) != tv.at(i))
                True = false;
        }
        if(True)
            std::cout << "Colliding with AABB works correctly" << std::endl;

        bool cvsaabbres = a.collideWithCircle(circle_center, radius);
#ifdef PRINT_RESULTS
        std::cout << cvsaabbres << std::endl;
#endif
    if(cvsaabbres)
        std::cout << "Colliding with circle works correctly" << std::endl;
}
