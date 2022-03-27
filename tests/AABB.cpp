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
    //круги в левом верхнем углу
    //{
    inside.push_back((Circle) {{0.0, 0.0}, 1.0});
    inside.push_back((Circle) {{0.0, 0.0}, 0.0});
    //}
    //круги в правом верхнем углу
    //{
    inside.push_back((Circle) {{5.0, 0.0}, 1.0});
    inside.push_back((Circle) {{5.0, 0.0}, 0.0});
    //}
    //круги в левом нижнем углу
    //{
    inside.push_back((Circle) {{0.0, 5.0}, 1.0});
    inside.push_back((Circle) {{0.0, 5.0}, 0.0});
    //}
    //круги в правом нижнем углу
    //{
    inside.push_back((Circle) {{5.0, 5.0}, 1.0});
    inside.push_back((Circle) {{5.0, 5.0}, 0.0});
    //}
    //круги на одной прямой с левым верхним углом
    //{
    inside.push_back((Circle) {{0.0, -1.0}, 2.0});
    inside.push_back((Circle) {{0.0, -1.0}, 1.0});
    inside.push_back((Circle) {{-1.0, 0.0}, 2.0});
    inside.push_back((Circle) {{-1.0, 0.0}, 1.0});
    //}
    //круги на одной прямой с правым верхним углом
    //{
    inside.push_back((Circle) {{5.0, -1.0}, 2.0});
    inside.push_back((Circle) {{5.0, -1.0}, 1.0});
    inside.push_back((Circle) {{4.0, 0.0}, 2.0});
    inside.push_back((Circle) {{4.0, 0.0}, 1.0});
    //}
    //круги на одной прямой с левым нижжним углом
    //{
    inside.push_back((Circle) {{0.0, 4.0}, 2.0});
    inside.push_back((Circle) {{0.0, 4.0}, 1.0});
    inside.push_back((Circle) {{-1.0, 5.0}, 2.0});
    inside.push_back((Circle) {{-1.0, 5.0}, 1.0});
    //}
    //круги на одной линии с правым нижним углом
    //{
    inside.push_back((Circle) {{5.0, 4.0}, 2.0});
    inside.push_back((Circle) {{5.0, 4.0}, 1.0});
    inside.push_back((Circle) {{4.0, 5.0}, 2.0});
    inside.push_back((Circle) {{4.0, 5.0}, 1.0});
    //}
    //круги снаружи со стороны левого верхнего угла
    //{
      //будет позже
    //}
    //круги снаружи со стороны правого верхнего угла
    //{
      //будет позже
    //}
    //круги снаружи со стороны левого нижнего угла
    //{
      //будет позже
    //}
    //круги снаружи со стороны правого нижнего угла
    //{
      //будет позже
    //}
    //круги снаружи у левой стороны
    //{
      //будет позже
    //}
    //круги снаружи у верхней стороны
    //{
      //будет позже
    //}
    //круги снаружи у нижней стороны
    //{
      //будет позже
    //}
    //круги снаружи у правой стороны
    //{
      //будет позже
    //}
    //круг внутри
    //{
      //будет позже
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
      //будет позже
    //} круги вне коллизии с test1

    //} круги и test1

    std::cout << "All tests passed sucessfully!" << std::endl;
    return 0;
}
