#include "types.hpp"
#include <math/gmath.hpp>

f32 GMath::barycentric(f32 val1, f32 val2, f32 val3, f32 amount1, f32 amount2) {
    return val1 + (val2 - val1) * amount1 + (val3 - val1) * amount2;
}

f32 GMath::clamp(f32 val, f32 min, f32 max) {
    val = (val > max) ? max : val;
    val = (val < min) ? min : val;

    return val;
}

f32 GMath::absolute(f32 val) {
    if (val < 0)
        val = -val;

    return val;
}

f32 GMath::distance(f32 val, f32 val2) {
    return GMath::absolute(val - val2);
}

/*Performs a hermite spine interpolation*/
f32 GMath::hermite(f32 val, f32 tang,
                          f32 val2, f32 tang2, f32 amount) {
    f64 v1 = val;
    f64 v2 = val2;
    f64 t1 = tang;
    f64 t2 = tang2;
    f64 s = amount;
    f64 result = 0;

    f64 s_cubed = s * s * s;
    f64 s_squared = s * s;

    if (amount == 0.0f)
        result = val;
    else if (amount == 1.0f)
        result = val2;
    else
        result = (2 * v1 - 2 * v2 + t2 + t1) * s_cubed +
            (3 * v2 - 3 * v1 - 2 * t1 - t2) * s_squared +
            t1 * s + v1;

    return (f32)result;
}

f32 GMath::lerp(f32 val, f32 val2, f32 amount) {
    return val + (val2 - val) * amount;
}

f32 GMath::max(f32 val, f32 val2) {
    return val > val2 ? val : val2;
}

f32 GMath::min(f32 val, f32 val2) {
    return val < val2 ? val : val2;
}

f32 GMath::smooth_step(f32 val, f32 val2, f32 amount) {
    f32 result = clamp(amount, 0.0f, 1.0f);
    return hermite(val, 0.0f, val2, 0.0f, result);
}

f32 GMath::to_degrees(f32 radians) {
    return (f32)(radians * 57.295779513082320876798154814105);
}

f32 GMath::to_radians(f32 degrees) {
    return (float)(degrees * 0.017453292519943295769236907684886);
}

i32 GMath::clamp(i32 val, i32 min, i32 max) {
    val = (val > max) ? max : val;
    val = (val < min) ? min : val;

    return val;
}

i32 GMath::max(i32 val, i32 val2) {
    return val > val2 ? val : val2;
}

i32 GMath::min(i32 val, i32 val2) {
    return val < val2 ? val : val2;
}

bool GMath::is_power_of_two(i32 val) {
    return (val > 0) && ((val & (val - 1)) == 0);
}
