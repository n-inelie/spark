#include "callbacks.hxx"
#include <iostream>

#include <GLFW/glfw3.h>

void window_set_all_callbacks(GLFWwindow *window) {
    glfwSetWindowCloseCallback(window, window_close_callback);
    glfwSetKeyCallback(window, key_callback);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {
    (void)scancode;
    (void)mods;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void window_close_callback(GLFWwindow *window) {
    (void)window;
    std::cout << "Spark extinguished\n";
}
