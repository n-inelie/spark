#include <iostream>

#include <GLFW/glfw3.h>

#include "callbacks.hxx"

void window_set_all_callbacks(GLFWwindow *window) {
    glfwSetWindowCloseCallback(window, window_close_callback);
    glfwSetKeyCallback(window, key_callback);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {
    (void)scancode;
    (void)mods;
    if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        default:
            break;
        }
    }
}

void window_close_callback(GLFWwindow *window) {
    (void)window;
    std::cout << "Spark extinguished\n";
}
