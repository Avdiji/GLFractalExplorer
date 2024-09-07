#pragma once
#include <BaseFractal.hpp>
#include <chrono>
#include <thread>

BaseFractal::~BaseFractal() {
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
    glDeleteBuffers(1, &_EBO);
    glDeleteProgram(_shaderProgram);

    glfwDestroyWindow(_window);
    glfwTerminate();
}

void BaseFractal::initializeWindow(const std::string& p_windowTitle) {
    if (!glfwInit()) { throw WindowInitializationError(); }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    _window = glfwCreateWindow(_width, _height, p_windowTitle.c_str(), nullptr, nullptr);
    if (!_window) {
        glfwTerminate();
        throw WindowCreationError();
    }
    glfwMakeContextCurrent(_window);
    gladLoadGL();
}

void BaseFractal::createShaderProgram() {
    // Create and compile vertex shader
    _vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(_vertexShader, 1, &_vertexShaderSource, nullptr);
    glCompileShader(_vertexShader);
    // catch shader exception
    GLint success;
    glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glDeleteShader(_vertexShader);
        throw ShaderError(GL_VERTEX_SHADER, _vertexShader);
    }

    // Create and compile fragment shader
    const char* fragmentShaderSource = getFragmentShaderSource();
    _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(_fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(_fragmentShader);
    glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glDeleteShader(_fragmentShader);
        throw ShaderError(GL_FRAGMENT_SHADER, _fragmentShader);
    }

    // Link shaders into a shader program
    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, _vertexShader);
    glAttachShader(_shaderProgram, _fragmentShader);
    glLinkProgram(_shaderProgram);
    glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
    if (!success) { throw ShaderLinkingError(_shaderProgram); }

    // Cleanup shaders as they're now linked into our program
    glDeleteShader(_vertexShader);
    glDeleteShader(_fragmentShader);
}

void BaseFractal::setupBuffers() {
    const float vertices[] = {
        -1.0f, -1.0f,  // Bottom-left
        1.0f,  -1.0f,  // Bottom-right
        -1.0f, 1.0f,   // Top-left
        1.0f,  1.0f    // Top-right
    };

    const unsigned int indices[] = {
        0, 1, 2,  // First triangle
        2, 1, 3   // Second triangle
    };

    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    glGenBuffers(1, &_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void BaseFractal::renderFractal() {
    while (!glfwWindowShouldClose(_window)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        doOnRenderStart();

        if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(_window, true);

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(_shaderProgram);
        setUniforms();

        glBindVertexArray(_VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(_window);
        glfwPollEvents();

        doOnRenderEnd();
    }
}