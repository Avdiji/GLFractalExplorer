#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <string>

/**
 * Throw, when a OpenGL shader can not be compiled.
 */
class ShaderException : public std::runtime_error {
    public:
        ShaderException(const GLuint &p_shader) : std::runtime_error(createErrorMessage(p_shader)) {}

    private:
        static std::string createErrorMessage(const GLuint &p_shader) {
            GLint success;
            GLchar infolog[512];

            glGetShaderiv(p_shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(p_shader, 512, nullptr, infolog);
                return std::string("Shader compilation failed: ") + std::string(infolog);
            } else {
                return std::string("No compilation errors, exception should not be thrown.");
            }
        }
};

/**
 * Throw, when Shaders can not be linked.
 */
class ShaderLinkingError : public std::runtime_error {
    public:
        ShaderLinkingError(const GLuint &program) : std::runtime_error(createErrorMessage(program)) {}

    private:
        static std::string createErrorMessage(const GLuint &program) {
            GLint success;
            GLchar infolog[512];

            glGetProgramiv(program, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(program, 512, nullptr, infolog);
                return std::string("Shader program linking failed: ") + std::string(infolog);
            } else {
                return std::string("No linking errors, exception should not be thrown.");
            }
        }
};
