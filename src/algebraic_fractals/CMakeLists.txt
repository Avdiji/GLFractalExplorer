set(MANDELBROT Mandelbrot)
add_executable(${MANDELBROT} Mandelbrot.cpp)
target_link_libraries(${MANDELBROT} ${BASE_FRACTAL})