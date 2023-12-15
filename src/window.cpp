#include <window.h>

void Window::init()
{
    // glClearColor(0.55f, 0.55f, 0.55f, 0.f);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

Window::Window(int width, int height, std::string title)
{
    std::cout << "from window: " << &renderer << '\n';
    if (!glfwInit()) {
       error("---------- cannot initialise glfw library ----------");
    }
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!window) {
        error("Error. Cannot create window!");
	}

   // glfwSetWindowAspectRatio(window, 1, 1);
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

   glfwMakeContextCurrent(window);
   gladLoadGL(glfwGetProcAddress);
   glfwSwapInterval(1);

   glfwGetFramebufferSize(window, &width, &height);
   framebuffer_size_callback(window, width, height);

   glfwSetTime(0.0);

   init();
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, std::max(width, 1), std::max(height, 1));	
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float) width / (float) height, 0.1f, 250.0);
	//gluOrtho2D(0, 100, 0, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Window::key_callback()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        close();
}

void Window::display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer->render();

    glFlush();
}

void Window::show()
{
    while (!glfwWindowShouldClose(window)) {
        key_callback();

        display();

		glfwSwapBuffers(window);
		glfwPollEvents();
    }
}

void Window::close()
{
    glfwSetWindowShouldClose(window, true);
}
