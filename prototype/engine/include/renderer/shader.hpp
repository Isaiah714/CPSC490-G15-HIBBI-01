#pragma once

#include "glad/glad.h"
#include <iostream>
#include <fstream>
#include <sstream>


/**
 * @brief Compiles a shader from a given source file path
 * @param path The specified path to the shader, relative to the build path (e.g. ../assets/shaders)
 * @param type The shader type to be compiled (e.g. GL_VERTEX_SHADER, GL_FRAGMENT_SHADER)
 * @return The OpenGL ID for the successully created shader
 */
unsigned int createShader(std::string path, unsigned int type) {
    std::ifstream shaderStream(path);
    if (!shaderStream.is_open()) {
        std::cerr << "Failed to open shader at " << path;
    }
    std::stringstream shaderSStream;
    shaderSStream << shaderStream.rdbuf();
    std::string shaderSourceStr = shaderSStream.str();
    const GLchar* shaderSourceCStr = shaderSourceStr.c_str();

    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSourceCStr, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        glDeleteShader(shader); 
        std::cerr << "Shader Compilation Failed (" + path + "):\n" + std::string(infoLog);
    }
    return shader;
}