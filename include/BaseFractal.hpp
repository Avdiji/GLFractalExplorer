#pragma once
#include <IFractal.hpp>

/**
 * Abstract Class acts as the Base of every Concrete Fractal.
 */
class BaseFractal : public IFractal {
    public:
        /**
         * Initialize a Fullscreen OpenGL window.
         *
         * @param p_windowTitle Title of the window.
         */
        void initializeWindow(const std::string &p_windowTitle);

        /**
         * Create a ShaderProgram.
         * The vertexShader should be identical for all Fractals and thus doesnt need to be dynamic.
         *
         * @param p_fragmentShaderSource Path to the fragment Shader.
         */
        void createShaderProgram(const std::string &p_fragmentShaderSource);

        /**
         * Setup the VAO, VBO, EBO and everything surrounding that.
         */
        void setupBuffers();

        /**
         * Render the Fractal.
         */
        void renderFractal();

    private:
        // resolution
        const float _width = 1920;
        const float _height = 1080;

        // Buffer ID's
        GLuint _VAO, _VBO, _EBO;

        // Shader ID's
        GLuint _vertexShader, _fragmentShader, _shaderProgram;

        // Window
        GLFWwindow *_window;
};