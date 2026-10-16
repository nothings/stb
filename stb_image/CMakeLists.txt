add_library(
    stb_image STATIC
    stb_image.cpp
)

add_library(stb::stb_image ALIAS stb_image)

target_include_directories(
    stb_image
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)