#include "window.hpp"
#include <glad/glad.h>

Window::Window(const u32 _width, const u32 _height) {
    width = _width;
    height = _height;
}

bool Window::create() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return false;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow(
        "Window",
        width,
        height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        SDL_Quit();
        return false;
    }

    if (!create_gl_context()) {
        return false;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        SDL_GL_DestroyContext(gl_context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    glViewport(0, 0, width, height);
    return true;
}

void Window::destroy() {
    SDL_GL_DestroyContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::update_size(SDL_Event &event) {
    width = event.window.data1;
    height = event.window.data2;
    glViewport(0, 0, width, height);
}

u32 Window::get_height() {
    return height;
}

u32 Window::get_width() {
    return width;
}

auto Window::get_window() -> SDL_Window * {
    return window;
}

bool Window::create_gl_context() {
    gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    return true;
}
