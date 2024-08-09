#pragma once

#include <cstdio>
#include <cstdlib>
#include <iostream>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#define BUFFER_SIZE 4096

class Shader {
  public:
    unsigned int ID;

    Shader(const char *vertexSourcePath, const char *fragSourcePath) {
        FILE *vertexFile = fopen(vertexSourcePath, "rb");
        if (!vertexFile) {
            std::cerr << "[ERROR] Failed to open vertex source ("
                      << vertexSourcePath << ")\n";
            exit(EXIT_FAILURE);
        }
        FILE *fragFile = fopen(fragSourcePath, "rb");
        if (!fragFile) {
            std::cerr << "[ERROR] Failed to open fragment source ("
                      << vertexSourcePath << ")\n";
            exit(EXIT_FAILURE);
        }

        char *vertexSource = (char *)malloc(sizeof(char) * BUFFER_SIZE);
        char *fragSource = (char *)malloc(sizeof(char) * BUFFER_SIZE);

        fread(vertexSource, sizeof(char), BUFFER_SIZE, vertexFile);
        fread(fragSource, sizeof(char), BUFFER_SIZE, fragFile);

        fclose(vertexFile);
        fclose(fragFile);

        unsigned int vertex, fragment;

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexSource, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragSource, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");

        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void use() { glUseProgram(ID); }

    void deleteProgram() { glDeleteProgram(ID); }

  private:
    void checkCompileErrors(unsigned int shader, std::string type) {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout
                    << "[ERROR] Failed to compile shader of type " << type
                    << "\n"
                    << infoLog
                    << "\n -- "
                       "--------------------------------------------------- -- "
                    << std::endl;
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout
                    << "[ERROR] Failed to link program of type " << type << "\n"
                    << infoLog
                    << "\n -- "
                       "--------------------------------------------------- -- "
                    << std::endl;
            }
        }
    }
};
