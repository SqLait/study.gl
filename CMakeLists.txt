cmake_minimum_required(VERSION 3.20)
project(study LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wstrict-prototypes \
    -Wall -Wno-sign-compare -Wpointer-arith -Wformat-security -Wswitch-enum \
    -Wunused-parameter -Wstrict-aliasing -Wbad-function-cast -Wcast-align \
    -Wstrict-prototypes -Wold-style-definition -Wmissing-field-initializers \
    -Wno-override-init"
)

include(cmake/pkg.cmake)

add_executable(main
    src/main.cpp
    src/window.cpp
)

add_subdirectory(include)

target_link_libraries(main PRIVATE SDL3::SDL3 glm::glm lib util)
