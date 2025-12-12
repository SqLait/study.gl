add_library(util STATIC)

target_sources(util
        PUBLIC
        src/shader.cpp
        src/gfx_debug.cpp
)

target_include_directories(util
        PUBLIC
        include
)

target_link_libraries(util PUBLIC lib)
