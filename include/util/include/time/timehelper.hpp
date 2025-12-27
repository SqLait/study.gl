#pragma once

#include "types.hpp"

class TimeHelper {
    f32 delta = 0;
    f32 prev_delta = 0;

public:
    f32 delta_time();
    f32 time();
};
