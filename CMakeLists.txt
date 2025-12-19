cmake_minimum_required(VERSION 3.20)
project(study LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/pkg.cmake)

add_executable(main
    src/main.cpp
    src/window.cpp
)

target_compile_options(main PRIVATE
    -Wall
    -Wextra
    -Wpointer-arith
    -Wformat-security
    -Wswitch-enum
    -Wunused-parameter
    -Wstrict-aliasing
    -Wbad-function-cast
    -Wcast-align
    -Wold-style-definition
    -Wmissing-field-initializers
    -Wno-sign-compare
    -Wno-override-init
)

add_subdirectory(include)

target_link_libraries(main PRIVATE SDL3::SDL3 glm::glm lib util)
