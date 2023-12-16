#include <entity.h>

void Entity::add(std::shared_ptr<Shape> component)
{
    this->component.emplace_back(component);
}

void Entity::render()
{
    // std::cout << "calling entity render function\n";
    for (const auto& comp : component) {
        comp->render();
    }
    // std::cout << component.size() << '\n';
}

unsigned int Entity::size() 
{
    return component.size();
}
