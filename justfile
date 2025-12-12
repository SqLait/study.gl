set shell := ["/usr/bin/env", "bash", "-c"]
set windows-shell := ["pwsh.exe", "-NoLogo", "-noprofile", "-c"]

# Initialises CMake and other project specific logic. (Run at the root of the project)
[group('configure')]
init:
    cmake -S . -B build
    cmake --build build

# Build and execute the project.
[group('build')]
run:
    cmake --build build
    @./build/main
    
# Builds the project.
[group('build')]
build:
    cmake --build build

# Cleans the build directory and  reinitialises
[group('build')]
clean:
    rm -rf build
    mkdir build
    just init

# Creates a release binary 
[group('publish')]
release:
    just _release-{{ os () }}


_release-windows: build

_release-mac: build

_release-linux: build
