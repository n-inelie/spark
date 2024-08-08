#include "callbacks.hxx"
#include <iostream>

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#define WIDTH 800
#define HEIGHT 500

int main(void) {
    std::cout << "Spark Ignited\n";

    if (!glfwInit()) {
        std::cerr << "[ERROR] Failed to initialize glfw\n";
        return -1;
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow *window =
        glfwCreateWindow(WIDTH, HEIGHT, "spark", nullptr, nullptr);
    glViewport(0, 0, WIDTH, HEIGHT);

    glfwMakeContextCurrent(window);

    window_set_all_callbacks(window);

    glClearColor(1.0f, 0.5f, 1.0f, 1.0f);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
