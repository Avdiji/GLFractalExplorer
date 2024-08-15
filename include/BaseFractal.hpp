#pragma once

#include <IFractal.hpp>

/**
 * Abstract Class acts as the Base of every Concrete Fractal.
 *
 * In order to create a Concrete Fractal you must at least override the getFragmentShaderSource method, to provide a
 * proper shader.
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
         * @throws ShaderError if one of the shaders contain errors.
         * @throws ShaderLinkingError if the shaderProgram is invalid.
         */
        void createShaderProgram() override;

        /**
         * Setup the VAO, VBO, EBO and everything surrounding that.
         */
        void setupBuffers() override;

        /**
         * Render the Fractal.
         */
        void renderFractal() override;

        /**
         * The corresponding FragmentShader, used to render the fractal.
         *
         * @return The Fragment Shader, which eventually created the fractal.
         */
        const char *getFragmentShaderSource() override { return ""; }

        /**
         * Set the Uniforms of the corresponding Fractal
         */
        void setUniforms() override {}

        /**
         * Method will be executed each time a new frame is being rendered
         */
        void doOnRenderStart() override {}

        /**
         * Method will be executed on the end of each rendered frame.
         */
        void doOnRenderEnd() override {}

    protected:
        // Shader Program (Protected to be able to access uniforms)
        GLuint _shaderProgram;

        // resolution
        const float _width = 1920;
        const float _height = 1080;

        // Window
        GLFWwindow *_window;

        // Buffer ID's
        GLuint _VAO, _VBO, _EBO;

        // Shader ID's
        GLuint _vertexShader, _fragmentShader;

    private:
        const char *_vertexShaderSource = R"(
            #version 330 core
            layout(location = 0) in vec2 aPos;
            void main() {
                gl_Position = vec4(aPos, 0.0, 1.0);
            }
        )";
};