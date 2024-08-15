#pragma once

#include <IFractal.hpp>

/**
 * Abstract Class acts as the Base of every Concrete Fractal.
 */
class BaseFractal : public IFractal {
    public:
        /**
         * Destructor.
         *
         * Unbind all Buffers, Programs, etc...
         * Delete all Buffers, Programs, etc...
         */
        ~BaseFractal();

        /**
         * Initialize a Fullscreen OpenGL window.
         *
         * @param p_windowTitle Title of the window.
         *
         * @throws WindowInitializationError, if openGL couldn't be initialized.
         * @throws WindowCreationError, if Opengl failed to create a window.
         */
        void initializeWindow(const std::string &p_windowTitle) override;

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
        void createShaderProgram(const std::string &p_fragmentShaderSource) override;

        /**
         * Setup the VAO, VBO, EBO and everything surrounding that.
         */
        void setupBuffers() override;

        /**
         * Render the Fractal.
         */
        void renderFractal() override;

        /**
         * Set the Uniforms of the corresponding Fractal
         */
        void setUniforms() override;

        /**
         * Method will be executed each time a new frame is being rendered
         */
        void doOnRenderStart() override;

        /**
         * Method will be executed on the end of each rendered frame.
         */
        void doOnRenderEnd() override;

    protected:
        // Shader Program (Protected to be able to access uniforms)
        GLuint _shaderProgram;

    private:
        // resolution
        const float _width = 1920;
        const float _height = 1080;

        // Buffer ID's
        GLuint _VAO, _VBO, _EBO;

        // Shader ID's
        GLuint _vertexShader, _fragmentShader;

        // Window
        GLFWwindow *_window;
};