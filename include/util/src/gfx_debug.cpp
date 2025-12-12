#include <gfx/debug.hpp>
#include <glad/glad.h>
#include <iostream>

static void gl_clear_error() {
    while (glGetError() != GL_NO_ERROR);
}

static bool gl_log_call() {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Err] (" << error << ")\n";
        return false;
    }
    return true;
}
