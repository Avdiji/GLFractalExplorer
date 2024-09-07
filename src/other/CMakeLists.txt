set(SHADERHOTLOADING ShaderHotloading)
add_executable(${SHADERHOTLOADING} ShaderHotloading.cpp)
target_link_libraries(${SHADERHOTLOADING} ${BASE_FRACTAL})

# Specify the installation directory and install the executable
install(TARGETS ${SHADERHOTLOADING} DESTINATION bin)