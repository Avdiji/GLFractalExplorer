#pragma once
#include <BaseFractal.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

class ShaderHotloading : public BaseFractal {
    public:
        const char* getFragmentShaderSource() override {
            // open the fragment shader to hotload
            std::fstream filestream("C:/Dev_Avdiji/Development/GLFractalExplorer/src/other/resources/shader.frag");
            if (!filestream) { throw new std::runtime_error("Failed to open Fragment Shader file."); }

            // read the fragment shader to hotload
            std::stringstream buffer;
            buffer << filestream.rdbuf();

            currentFragmentShader = buffer.str();
            return currentFragmentShader.c_str();
        }

        void setUniforms() override {
            float currentTime = static_cast<float>(glfwGetTime());
            glUniform1f(glGetUniformLocation(_shaderProgram, "iTime"), currentTime);

        }
        void doOnRenderStart() override { createShaderProgram(); }
        void doOnRenderEnd() {}

    private:
        std::string currentFragmentShader;
};

int main() {
    try {
        ShaderHotloading shaderHotloading;
        shaderHotloading.initializeWindow("ShaderHotloading");
        shaderHotloading.createShaderProgram();
        shaderHotloading.setupBuffers();
        shaderHotloading.renderFractal();
    } catch (std::runtime_error& e) { std::cerr << e.what() << std::endl; }
}
