#include <BaseFractal.hpp>
#include <algorithm>  // For std::min
#include <chrono>
#include <cmath>
#include <thread>

class Mandelbrot : public BaseFractal {
    public:
        const char* getFragmentShaderSource() override {
            return R"(
            #version 330 core
            #extension GL_ARB_gpu_shader_fp64 : enable
            out vec4 FragColor;
            uniform vec2 u_resolution;
            uniform vec2 u_center;
            uniform float u_scale;
            uniform int u_maxIterations;

            vec3 getColor(float iteration, float maxIterations) {
                float t = iteration / maxIterations;
                vec3 color = vec3(0.0, 0.0, 0.0);
                if (t < 0.16) {
                    color = mix(vec3(0.0, 0.0, 0.4), vec3(0.6, 1.0, 1.0), t / 0.16);
                } else if (t < 0.42) {
                    color = mix(vec3(0.0, 0.4, 1.0), vec3(0.4, 1.0, 1.0), (t - 0.16) / 0.26);
                } else if (t < 0.6425) {
                    color = mix(vec3(1.0, 1.0, 0.0), vec3(1.0, 0.5, 0.0), (t - 0.42) / 0.2225);
                } else if (t < 0.8575) {
                    color = mix(vec3(1.0, 0.5, 0.0), vec3(1.0, 0.9, 1.0), (t - 0.6425) / 0.215);
                } else {
                    color = mix(vec3(1.0, 0.0, 0.0), vec3(0.0, 0.0, 0.0), (t - 0.8575) / 0.1425);
                }
                return color;
            }

            void main() {
                // Use double precision constants directly
                dvec2 c = dvec2(u_center) + dvec2(gl_FragCoord.xy - u_resolution / 2.0) * double(u_scale);
                dvec2 z = dvec2(0.0, 0.0);
                int i;
                for (i = 0; i < u_maxIterations; i++) {
                    if (length(z) > 2.0) break;
                    z = dvec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
                }
                vec3 finalColor = getColor(float(i), float(u_maxIterations));
                FragColor = vec4(finalColor, 1.0);
            }
        )";
        }

        void setUniforms() override {
            glUniform2f(glGetUniformLocation(_shaderProgram, "u_resolution"), _width, _height);
            glUniform2f(glGetUniformLocation(_shaderProgram, "u_center"), _anchor.first + _center.first * _scale,
                        _anchor.second + _center.second * _scale);
            glUniform1f(glGetUniformLocation(_shaderProgram, "u_scale"), _scale / _width);

            // Dynamic iteration count based on zoom level with a cap
            int dynamicIterations = static_cast<int>(300 + 50 * sqrt(log(10.0f / _scale)));
            dynamicIterations = std::min(dynamicIterations, 1000);  // Cap the iterations to 1000
            glUniform1i(glGetUniformLocation(_shaderProgram, "u_maxIterations"), dynamicIterations);
        }

        void doOnRenderStart() override {
            // Zoom (W/S)
            if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
                updateAnchor();
                _scale *= 0.9f;
            }
            if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
                updateAnchor();
                _scale /= 0.9f;
            }

            // Move (Arrow Keys)
            float baseMoveAmount = 0.01f;
            float minMoveAmount = 1e-7f;  // Minimum movement threshold
            float moveAmount = std::max(baseMoveAmount / std::log(_scale + 3.0f), minMoveAmount);
            if (glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS) { _center.second += moveAmount; }
            if (glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS) { _center.second -= moveAmount; }
            if (glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS) { _center.first -= moveAmount; }
            if (glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS) { _center.first += moveAmount; }
        }

    private:
        float _scale = 5.0f;
        std::pair<float, float> _center = {0.0f, 0.0f};
        std::pair<float, float> _anchor = {-0.5f, 0.0f};  // Initial anchor at the Mandelbrot set's center

        void updateAnchor() {
            // Recenter the fractal by updating the anchor and resetting _center to a small value
            _anchor.first += _center.first * _scale;
            _anchor.second += _center.second * _scale;
            _center = {0.0f, 0.0f};
        }
};

int main() {
    Mandelbrot mandelbrot;
    mandelbrot.initializeWindow("Mandelbrot");
    mandelbrot.createShaderProgram();
    mandelbrot.setupBuffers();
    mandelbrot.renderFractal();
}
