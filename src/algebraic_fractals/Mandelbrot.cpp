#pragma once
#include <BaseFractal.hpp>
#include <iomanip>
#include <iostream>

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

                    if (t < 0.1) {
                        color = mix(vec3(0.1, 0.1, 0.3), vec3(0.3, 0.2, 0.7), t / 0.1); // Dark blue to purple
                    } else if (t < 0.2) {
                        color = mix(vec3(0.3, 0.2, 0.7), vec3(0.5, 0.3, 0.5), (t - 0.1) / 0.1); // Purple to violet
                    } else if (t < 0.3) {
                        color = mix(vec3(0.5, 0.3, 0.5), vec3(0.6, 0.2, 0.3), (t - 0.2) / 0.1); // Violet to burgundy
                    } else if (t < 0.4) {
                        color = mix(vec3(0.6, 0.2, 0.3), vec3(0.8, 0.3, 0.2), (t - 0.3) / 0.1); // Burgundy to orange
                    } else if (t < 0.5) {
                        color = mix(vec3(0.8, 0.3, 0.2), vec3(0.9, 0.6, 0.2), (t - 0.4) / 0.1); // Orange to golden yellow
                    } else if (t < 0.6) {
                        color = mix(vec3(0.9, 0.6, 0.2), vec3(0.6, 0.8, 0.4), (t - 0.5) / 0.1); // Golden yellow to olive green
                    } else if (t < 0.7) {
                        color = mix(vec3(0.6, 0.8, 0.4), vec3(0.2, 0.7, 0.4), (t - 0.6) / 0.1); // Olive green to teal
                    } else if (t < 0.8) {
                        color = mix(vec3(0.2, 0.7, 0.4), vec3(0.2, 0.5, 0.7), (t - 0.7) / 0.1); // Teal to blue-green
                    } else if (t < 0.9) {
                        color = mix(vec3(0.2, 0.5, 0.7), vec3(0.2, 0.3, 0.5), (t - 0.8) / 0.1); // Blue-green to deep blue
                    } else {
                        color = mix(vec3(0.2, 0.3, 0.5), vec3(0.0, 0.0, 0.0), (t - 0.9) / 0.1); // Deep blue to dark blue
                    }

                    return color;
                }

                void main() {
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
            glUniform2f(glGetUniformLocation(_shaderProgram, "u_center"), _center.first, _center.second);
            glUniform1f(glGetUniformLocation(_shaderProgram, "u_scale"), _scale / _width);

            // Dynamic iteration count based on zoom level with a cap
            int dynamicIterations = static_cast<int>(300 + 50 * sqrt(log(10.0f / _scale)));
            dynamicIterations = std::min(dynamicIterations, _iterations);  // Cap the iterations to 1000
            glUniform1i(glGetUniformLocation(_shaderProgram, "u_maxIterations"), dynamicIterations);
        }

        void doOnRenderStart() override {
            // print scale and location
            if (glfwGetKey(_window, GLFW_KEY_L) == GLFW_PRESS) {
                std::cout << std::endl;
                std::cout << "X val: " << std::setprecision(8) << _center.first << std::endl;
                std::cout << "Y val: " << std::setprecision(8) << _center.second << std::endl;
                std::cout << "Scale: " << _scale << std::endl;
            }

            // Zoom (W/S)
            if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) { _scale *= 0.95; }
            if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS && _scale < 8.0) { _scale /= 0.9; }

            // Move (Arrow Keys)
            double moveAmount = 0.005f * _scale;
            if (glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS) { _center.second += moveAmount; }
            if (glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS) { _center.second -= moveAmount; }
            if (glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS) { _center.first -= moveAmount; }
            if (glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS) { _center.first += moveAmount; }
        }

        void doOnRenderEnd() {}

    private:
        double _scale = 10.0f;
        int _iterations = 1000;
        // Up to 8 digits precision
        std::pair<double, double> _center = {-0.745428, 0.11301201};
        // std::pair<double, double> _center = {-1.74997970, 0};
        // std::pair<double, double> _center = {-0.76039999, 0.08277177};
        // std::pair<double, double> _center = {-0.74999879, 0.0071817112};
        // std::pair<double, double> _center = {0.19981936, 0.55382456};
        // std::pair<double, double> _center = {-0.85973844, 0.23495194};
        // std::pair<double, double> _center = {-0.73885270, 0.14167642};
        // std::pair<double, double> _center = {-1.4013633, 7.6094599e-05};
        // std::pair<double, double> _center = {0.26055793, 0.0017685117};
};

int main() {
    Mandelbrot mandelbrot;
    mandelbrot.initializeWindow("Mandelbrot");
    mandelbrot.createShaderProgram();
    mandelbrot.setupBuffers();
    mandelbrot.renderFractal();
}
