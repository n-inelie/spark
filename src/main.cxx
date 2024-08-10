#include <iostream>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "callbacks.hxx"
#include "shader.hxx"
#include "spark-utils.hxx"

#define WIDTH 800
#define HEIGHT 500

float vertices[] = {
    -0.5, -0.5, 0.0, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    0.5,  -0.5, 0.0, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
    0.5,  0.5,  0.0, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // top right
    -0.5, 0.5,  0.0, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // top left
    0.0,  0.0,  0.0, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // centre
};

unsigned int indices[] = {
    3, 4, 2, // first triangle
    0, 1, 4, // second triangle
};

int main(void) {
    std::cout << "Spark ignited\n";

    if (!glfwInit()) {
        std::cerr << "[ERROR] Failed to initialize glfw\n";
        return -1;
    }

    set_spark_glfw_hints();

    GLFWwindow *window = create_spark_window();

    glfwMakeContextCurrent(window);

    glViewport(0, 0, WIDTH, HEIGHT);

    window_set_all_callbacks(window);

    Shader shader("shaders/basic.vert.glsl", "shaders/basic.frag.glsl");

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int texture_width, texture_height, nrChannels;
    unsigned char *data = stbi_load("textures/sample1.jpg", &texture_width,
                                    &texture_height, &nrChannels, 0);

    if (!data) {
        std::cout << "Failed to load texture" << std::endl;
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0,
                     GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    shader.deleteProgram();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
