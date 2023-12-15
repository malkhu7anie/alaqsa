#include <window.h>

int main(void)
{

    auto ent = std::make_shared<Entity>();

    auto rect = std::make_shared<Rectangle>(20, 10);
    rect->translate(Coord{X, -4}, Coord{Y, -3}, Coord{Z, -40});
    ent->add(rect);

    auto circle = std::make_shared<Circle>(10);
    circle->translate(Coord{X, -4}, Coord{Y, -3}, Coord{Z, -70});
    circle->colour = {1, 0, 0};
    ent->add(circle);

    auto sphere = std::make_shared<Sphere>(20, 32, 22);
    sphere->translate(Coord{X, -50}, Coord{Y, -4}, Coord{Z, -120});
    sphere->colour = {0.5, 0.5, 0};
    ent->add(sphere);

    renderer->add(ent);
    Window window;
    window.show();
    // auto rect = Rectangle(1, 2);
    // rect.render();
    // rect.translate(Coord{Z
	return 0;
}
