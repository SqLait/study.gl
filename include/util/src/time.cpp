#include <time/time.hpp>
#include <SDL3/SDL_timer.h>

f32 Time::delta_time() {
    f32 current = (f32)SDL_GetTicks();
    delta = (current - prev_delta) / 1000.0f;
    prev_delta = current;
    return delta;
}

// Get the amount of time since the initialisation of the app
f32 Time::time() {
    return ((f32)SDL_GetTicks() / 1000);
}
