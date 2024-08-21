set(MANDELBROT Mandelbrot)
add_executable(${MANDELBROT} Mandelbrot.cpp)
target_link_libraries(${MANDELBROT} ${BASE_FRACTAL})

# Specify the installation directory and install the executable
install(TARGETS ${MANDELBROT} DESTINATION bin)