#ifndef COMPONENT_H
#define COMPONENT_H

#define _USE_MATH_DEFINES

#include <cmath>
#include <memory>
#include <vector>


#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include <glad/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <texture.h>


enum AXIS {
    X, Y, Z
};

struct Coord {
    AXIS axis;
    float val;
};

class Component {
public:
    std::vector<glm::vec4> transformed_vertex;
    std::vector<glm::vec4> vertex;
};

class Transform {
public:
    template <typename... Args>
        void translate(const Args&... coord)
        {
            changed = true;
            ((set(coord, __pos)), ...);
        }
    template <typename... Args>
        void rotate(const Args&... coord)
        {
            changed = true;
            ((set(coord, __rotate)), ...);
        }
    template <typename... Args>
        void scale(const Args&... coord)
        {
            changed = true;
            ((set(coord, __scale)), ...);
        }

    void set(const Coord& coord, glm::vec3& vert);
    std::vector<glm::vec4> transform(const std::vector<glm::vec4>&);

    bool changed = true;

    glm::vec3 __pos;
    glm::vec3 __rotate;
    glm::vec3 __scale = {1, 1, 1};
};

class Renderable : public Component, public Transform {
public:
    virtual void render(GLenum);
    glm::vec3 colour = {1, 1, 1};

    Texture texture;
    std::vector<glm::vec2> tex_cor;
};

class Shape : public Renderable {
public:
    virtual void render() = 0;
};

class Rectangle : public Shape {
public:
    Rectangle(const float& w, const float& h);
    void render();
};

class Circle : public Shape {
public:
    using T = float;
    Circle(const std::pair<T, T>& center, const T& radius, int count = 128);
    Circle(const T& radius, int count = 512);

    void render();
};


class Sphere : public Shape {
public: 
    Sphere();
    Sphere(const float& radius, const int& stacks, const int& slices);

    void render();
};

class Skybox : public Shape {
public:
    Skybox(const float& len);
    void draw(GLenum);
};

#endif
