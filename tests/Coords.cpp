#include "Coords.hpp"
#include <iostream>
#include <cassert>

int main()
{
    Coords c = {0.0, 0.0};
    Coords c1 = c;
    std::cout << "Copy constructor works correctly" << std::endl;
    assert(c == c1);
    std::cout << "Operator== works correctly" << std::endl;
    Coords c2 = {1.0, 1.0};
    assert(c != c2);
    std::cout << "Operator!= works correctly" << std::endl;
    c1 = c1 + c2;
    assert(c1 == c2);
    std::cout << "Operator+ works correctly" << std::endl;
    c1 = c1 - c2;
    assert(c1 == c);
    std::cout << "Operator- works correctly" << std::endl;
    assert(c1 < c2);
    assert(c2 > c1);
    c1 = c1 + (Coords) {1.0, 0.0};
    assert(c1 < c2);
    assert(c2 > c1);
    c1 = c + (Coords) {0.0, 1.0};
    assert(c1 < c2);
    assert(c2 > c1);
    std::cout << "Operator< and operator> work correctly" << std::endl;
    std::cout << "Tests complete" << std::endl;
    return 0;
}
