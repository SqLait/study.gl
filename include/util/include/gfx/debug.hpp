#pragma once
#include<types.hpp>

static void gl_clear_error();
static bool gl_log_call(const char *function, const char *file, i32 line);

#define GLCall(x) \
    gl_clear_error(); \
    x; \
    assert(gl_log_call); \

