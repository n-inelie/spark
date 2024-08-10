#pragma once

#include <GLFW/glfw3.h>

#define WIDTH 800 * 1.4
#define HEIGHT 500 * 1.4

void set_spark_glfw_hints();

GLFWwindow *create_spark_window();
