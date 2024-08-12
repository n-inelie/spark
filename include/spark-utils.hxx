#pragma once

#include <GLFW/glfw3.h>

constexpr uint32_t WIDTH = 800 * 1.4;
constexpr uint32_t HEIGHT = 500 * 1.4;

void set_spark_glfw_hints();

GLFWwindow *create_spark_window();
