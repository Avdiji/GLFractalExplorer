#pragma once

#include <exception/ShaderError.hpp>
#include <exception/WindowError.hpp>

/**
 * Interface - Class.
 * Declares Core Methods, to support (Fractal)Rendering using OpenGL
 */
class IFractal {
    public:
        /**
         * Initialize a Fullscreen OpenGL window.
         *
         * @param p_windowTitle Title of the window.
         *
         * @throws WindowInitializationError, if openGL couldn't be initialized.
         * @throws WindowCreationError, if Opengl failed to create a window.
         */
        virtual void initializeWindow(const std::string &p_windowTitle) = 0;

        /**
         * Create a ShaderProgram.
         * The vertexShader should be identical for all Fractals and thus doesnt need to be dynamic.
         *
         * @param p_fragmentShaderSource Path to the fragment Shader.
         *
         * @throws ShaderError if one of the shaders contain errors.
         * @throws ShaderLinkingError if the shaderProgram is invalid.
         * @throws MissingShader if a Shader was not found.
         */
        virtual void createShaderProgram(const std::string &p_fragmentShaderSource) = 0;

        /**
         * Setup the VAO, VBO, EBO and everything surrounding that.
         */
        virtual void setupBuffers() = 0;

        /**
         * Render the Fractal.
         */
        virtual void renderFractal() = 0;
};