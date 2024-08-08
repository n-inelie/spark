#pragma once

#include <GLFW/glfw3.h>

void window_set_all_callbacks(GLFWwindow *window);

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods);
void window_close_callback(GLFWwindow *window);
