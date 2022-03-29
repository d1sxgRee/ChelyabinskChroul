#include "Coords.hpp"
#include <iostream>
#include <cassert>

// ребята, я ещё допишу

int main()
{
    AABB test1 = {{0.0, 0.0}, {5.0, 5.0}}

    // тест фикстур с test1
    //{

    // фикстуры, которые должжны соприкосаться с test1
    //{
      //будет позже
    //} коллизии с test1

    // фикстуры, которые должны быть снаружи test1
    //{
      //будет позже
    //} без коллизии с test1

    //} фикстуры и test1

    // тест кругов
    //{

    // круги, которые должны соприкосаться с фикстурой
    //{
    std::vector<Circle> inside;
    // круги в левом верхнем углу
    //{
    inside.push_back((Circle) {{0.0, 0.0}, 1.0});
    inside.push_back((Circle) {{0.0, 0.0}, 0.0});
    //}
    // круги в правом верхнем углу
    //{
    inside.push_back((Circle) {{5.0, 0.0}, 1.0});
    inside.push_back((Circle) {{5.0, 0.0}, 0.0});
    //}
    // круги в левом нижнем углу
    //{
    inside.push_back((Circle) {{0.0, 5.0}, 1.0});
    inside.push_back((Circle) {{0.0, 5.0}, 0.0});
    //}
    // круги в правом нижнем углу
    //{
    inside.push_back((Circle) {{5.0, 5.0}, 1.0});
    inside.push_back((Circle) {{5.0, 5.0}, 0.0});
    //}
    // круги на одной прямой с левым верхним углом
    //{
    inside.push_back((Circle) {{0.0, -1.0}, 2.0});
    inside.push_back((Circle) {{0.0, -1.0}, 1.0});
    inside.push_back((Circle) {{-1.0, 0.0}, 2.0});
    inside.push_back((Circle) {{-1.0, 0.0}, 1.0});
    //}
    // круги на одной прямой с правым верхним углом
    //{
    inside.push_back((Circle) {{5.0, -1.0}, 2.0});
    inside.push_back((Circle) {{5.0, -1.0}, 1.0});
    inside.push_back((Circle) {{4.0, 0.0}, 2.0});
    inside.push_back((Circle) {{4.0, 0.0}, 1.0});
    //}
    // круги на одной прямой с левым нижжним углом
    //{
    inside.push_back((Circle) {{0.0, 4.0}, 2.0});
    inside.push_back((Circle) {{0.0, 4.0}, 1.0});
    inside.push_back((Circle) {{-1.0, 5.0}, 2.0});
    inside.push_back((Circle) {{-1.0, 5.0}, 1.0});
    //}
    // круги на одной линии с правым нижним углом
    //{
    inside.push_back((Circle) {{5.0, 4.0}, 2.0});
    inside.push_back((Circle) {{5.0, 4.0}, 1.0});
    inside.push_back((Circle) {{4.0, 5.0}, 2.0});
    inside.push_back((Circle) {{4.0, 5.0}, 1.0});
    //}
    // круги снаружи со стороны левого верхнего угла
    //{
    inside.push_back((Circle) {{-4.0, -3.0}, 5.0});
    inside.push_back((Circle) {{-1.0, -1.0}, 2.0});
    //}
    // круги снаружи со стороны правого верхнего угла
    //{
    inside.push_back((Circle) {{9.0, -3.0}, 5.0});
    inside.push_back((Circle) {{6.0, -1.0}, 2.0});
    //}
    // круги снаружи со стороны левого нижнего угла
    //{
    inside.push_back((Circle) {{-4.0, 8.0}, 5.0});
    inside.push_back((Circle) {{-1.0, 6.0}, 2.0});
    //}
    // круги снаружи со стороны правого нижнего угла
    //{
    inside.push_back((Circle) {{9.0, 8.0}, 5.0});
    inside.push_back((Circle) {{6.0, 6.0}, 2.0});
    //}
    // круги снаружи у левой стороны
    //{
    inside.push_back((Circle) {{-1.0, 2.5}, 1.0});
    inside.push_back((Circle) {{-1.0, 2.5}, 2.0});
    //}
    // круги снаружи у верхней стороны
    //{
    inside.push_back((Circle) {{2.5, -1.0}, 1.0});
    inside.push_back((Circle) {{2.5, -1.0}, 2.0});
    //}
    // круги снаружи у нижней стороны
    //{
    inside.push_back((Circle) {{2.5, 6.0}, 1.0});
    inside.push_back((Circle) {{2.5, 6.0}, 2.0});
    //}
    // круги снаружи у правой стороны
    //{
    inside.push_back((Circle) {{6.0, 2.5}, 1.0});
    inside.push_back((Circle) {{6.0, 2.5}, 2.0});
    //}
    // круги внутри
    //{
    inside.push_back((Circle) {{2.5, 2.5}, 1.0});
    inside.push_back((Circle) {{2.5, 2.5}, 2.5});
    inside.push_back((Circle) {{2.5, 2.5}, 3.0});
    inside.push_back((Circle) {{2.5, 2.5}, 10.0});
    //}

    std::cout
    << "Processing tests for circles colliding with fixture..."
    << std::endl;

    for(auto c: inside)
    {
        assert(test1.collideWithCircle(c));
    }
    std::cout << "...Done!" << std::endl;
    //} круги в коллизии с test1

    // круги, которые должны быть снаружи фикстуры
    //{
    std::vector<Circle> outside;
    // круги за левым верхним углом
      // ну потом допишу, извините, меня спать гонят

    std::cout
    << "Processing tests for circles not colliding with fixture..."
    << std::endl;

    for(auto c: outside)
    {
        assert(!test1.collideWithCircle(c));
    }
    std::cout << "...Done!" << std::endl;;
    //} круги вне коллизии с test1

    //} круги и test1

    std::cout << "All tests passed sucessfully!" << std::endl;
    return 0;
}