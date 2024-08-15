#pragma once

#include <GLFW/glfw3.h>

#include <string>

/**
 * Interface - Class.
 * Declares Core Methods, to support (Fractal)Rendering using OpenGL
 */
class IFractal {
    public:
        /**
         * Destructor.
         * Unbinds and deletes any buffers.
         */
        virtual ~IFractal() = 0;

        /**
         * Initialize a Fullscreen OpenGL window.
         *
         * @param p_windowTitle Title of the window.
         */
        virtual void initializeWindow(const std::string &p_windowTitle) = 0;

        /**
         * Create a ShaderProgram.
         * The vertexShader should be identical for all Fractals and thus doesnt need to be dynamic.
         *
         * @param p_fragmentShaderSource Path to the fragment Shader.
         */
        virtual void createShaderProgram(const std::string &p_fragmentShaderSource) = 0;

        /**
         * Bind the VAO
         */
        virtual void BindVAO() = 0;

        /**
         * Bind the VBO and EBO.
         */
        virtual void BindBuffers() = 0;

        /**
         * Unbind the VBO and EBO.
         */
        virtual void UnbindBuffers() = 0;

        /**
         * Render the Fractal.
         */
        virtual void renderFractal() = 0;

        /**
         * First function to be executed on rendering the Fractal.
         */
        virtual void onRenderStart() = 0;

        /**
         * Last function to be executed on rendering the Fractal.
         */
        virtual void onRenderEnd() = 0;

    private:
        // Buffer ID's
        GLuint _VAO, _VBO, _EBO;

        // Shader ID's
        GLuint _vertexShader, _fragmentShader, _shaderProgram;

        // Window
        GLFWwindow *_window;
};