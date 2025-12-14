#pragma once
#include <types.hpp>

class Shader {
    u32 id;
public:
    Shader(const char *vertex_path, const char *fragment_path);
    ~Shader();

    void use();
    void set_bool(const char *name, bool value);
    void set_i32(const char *name, i32 value);
    void set_f32(const char *name, f32 value);
    const u32 get_id();

private:
    void compile_shader(u32 shader, const char *glsl);
};
