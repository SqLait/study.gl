#pragma once
#include <span>
#include "glm/ext/matrix_float4x4.hpp"
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
    void set_mat4(const char *name, glm::mat4 value);
    u32 get_id();
    u32 get_uniform_location(const char *uniform);

private:
    void compile_shader(u32 shader, const char *glsl);
};
