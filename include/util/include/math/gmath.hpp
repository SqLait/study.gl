#pragma once

#include "types.hpp"
/*A helper class for common math calculations*/
class GMath {
public:
    GMath() = delete;
    static constexpr f32 E = 2.71828;
    static constexpr f32 LOG10E = 0.4342945f;
    static constexpr f32 LOG2E = 1.442695f;
    static constexpr f32 PI = 3.141592653589793;
    static constexpr f32 PI_OVER2 = (f32)(PI / 2.0);
    static constexpr f32 PI_OVER4 = (f32)(PI / 4.0);
    static constexpr f32 TAU = (f32)(PI * 2.0);

    static f32 barycentric(f32 val1, f32 val2, f32 val3, f32 amount1, f32 amount2);
    static f32 clamp(f32 val, f32 min, f32 max);
    static f32 absolute(f32 val);
    static f32 distance(f32 val, f32 val2);
    static f32 hermite(f32 val, f32 tang, f32 val2, f32 tang2, f32 amount);
    static f32 lerp(f32 val, f32 val2, f32 amount);
    static f32 max(f32 val, f32 val2);
    static f32 min(f32 val, f32 val2);
    static f32 smooth_step(f32 val, f32 val2, f32 amount);
    static f32 to_degrees(f32 radians);
    static f32 to_radians(f32 degrees);

    static i32 clamp(i32 val, i32 min, i32 max);
    static i32 max(i32 val, i32 val2);
    static i32 min(i32 val, i32 val2);

    static bool is_power_of_two(i32 val);
};
