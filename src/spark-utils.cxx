#include <iostream>

#include "spark-utils.hxx"

void set_spark_glfw_hints() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
}

GLFWwindow *create_spark_window() {

    GLFWwindow *window =
        glfwCreateWindow(WIDTH, HEIGHT, "spark", nullptr, nullptr);
    if (!window) {
        std::cerr << "[Error] Failed to create window\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    return window;
}
