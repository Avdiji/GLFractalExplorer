cmake_minimum_required(VERSION 3.28)

project(GLFractalExplorer)

set(CMAKE_CXX_STANDARD 17)
set(GL_FRACTAL_EXPLORER GLFractalExplorer)
set(BASE_FRACTAL BaseFractal)

# Setup OpenGL
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# include src directory
add_subdirectory(src)