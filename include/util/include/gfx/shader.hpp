#pragma once
#include <types.hpp>

class Shader {
    unsigned int id;
public:
    Shader(const char *vertex_path, const char *fragment_path);
    ~Shader();
    void use();

private:
    void compile_shader(u32 shader, const char *glsl);
};
