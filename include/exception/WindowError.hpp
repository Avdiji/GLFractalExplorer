#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <string>

/**
 * Throw, when glfwInit failed.
 */
class WindowInitializationError : public std::runtime_error {
    public:
        WindowInitializationError() : std::runtime_error("Unable to initialize OpenGL") {}
};

/**
 * Throw, when the application fails to create a Window.
 */
class WindowCreationError : public std::runtime_error {
    public:
        WindowCreationError() : std::runtime_error("Unable to create an OpenGL-Window") {}
};