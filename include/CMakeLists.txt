target_sources(
    ${BASE_FRACTAL}
    PUBLIC FILE_SET
    HEADERS
    BASE_DIRS
    ${CMAKE_SOURCE_DIR}/include/
    FILES
    IFractal.hpp
    BaseFractal.hpp
    exception/ShaderException.hpp
)