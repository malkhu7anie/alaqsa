#ifndef WINDOW_H
#define WINDOW_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <glad/gl.h>
#include <GL/glu.h>

#include <utils.h>
#include <renderer.h>

class Window {
public:
    Window(int width = 540, int height = 400, std::string title = "window");

    void init();
    void show();
    void display();
    void close();
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void key_callback();

private:
    GLFWwindow *window;
};

#endif
