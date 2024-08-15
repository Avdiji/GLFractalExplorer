# find openGL package
find_package(glfw3 REQUIRED)

# create library for BaseFractals
add_library(${BASE_FRACTAL} BaseFractal.cpp)
add_subdirectory(${PROJECT_SOURCE_DIR}/include include)
add_subdirectory(${PROJECT_SOURCE_DIR}/dependencies dependencies)

# Link OpenGL and glad to the library
target_link_libraries(${BASE_FRACTAL} glfw)
target_link_libraries(${BASE_FRACTAL} Glad)
