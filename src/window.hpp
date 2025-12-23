#pragma once

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_video.h"
#include <SDL3/SDL.h>
#include <types.hpp>

class Window {
    SDL_Window* window = nullptr;
    SDL_GLContext gl_context;

    u32 width;
    u32 height;

public:
    Window(const u32 _width, const u32 _height);

    bool create();
    void destroy();
    void update_size(SDL_Event &event);
    auto get_window() -> SDL_Window *;
    u32 get_height();
    u32 get_width();
private:
    bool create_gl_context();
};
