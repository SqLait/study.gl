add_library(lib STATIC)

target_sources(lib
        PUBLIC
        src/glad.c
)

target_include_directories(lib
        PUBLIC
        include
)
