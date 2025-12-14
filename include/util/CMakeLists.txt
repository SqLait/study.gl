add_library(util STATIC)

target_sources(util
        PUBLIC
        src/shader.cpp
        src/gfx_debug.cpp
        src/stb_images.cpp
        src/texture.cpp
)

target_include_directories(util
        PUBLIC
        include
)

target_link_libraries(util PUBLIC lib)
