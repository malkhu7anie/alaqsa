#ifndef ENTITY_H
#define ENTITY_H

#include <component.h>

class Entity {
public:
    void add(std::shared_ptr<Shape> component);
    void render();
    unsigned int size();

private:
    std::vector<std::shared_ptr<Shape>> component;
};

#endif
