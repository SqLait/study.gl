#include <time/timehelper.hpp>
#include <SDL3/SDL_timer.h>

f32 TimeHelper::delta_time() {
    f32 current = (f32)SDL_GetTicks();
    delta = (current - prev_delta) / 1000.0f;
    prev_delta = current;
    return delta;
}

// Get the amount of time since the initialisation of the app
f32 TimeHelper::time() {
    return ((f32)SDL_GetTicks() / 1000);
}
