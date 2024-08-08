#include "callbacks.hxx"
#include <iostream>

#include <GLFW/glfw3.h>

void window_set_all_callbacks(GLFWwindow *window) {
    glfwSetWindowCloseCallback(window, window_close_callback);
}

void window_close_callback(GLFWwindow *window) {
    (void)window;
    std::cout << "Spark extinguished\n";
}
