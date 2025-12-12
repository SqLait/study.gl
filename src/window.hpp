#pragma once

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_video.h"
#include <SDL3/SDL.h>
#include <glad/glad.h>

class Window {
    SDL_Window* window = nullptr;
    SDL_GLContext gl_context;

    int width;
    int height;

public:
    Window(const int _width, const int _height);

    bool create();
    void destroy();
    void update_size(SDL_Event &event);
    auto get_window() -> SDL_Window *;
private:
    bool create_gl_context();
};
