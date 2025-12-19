#pragma once
#include "types.hpp"
#include <span>
#include <vector>

class Object {
    std::vector<f32> vertices;
    std::vector<u32> indices;
public:
    u32 vao;
    u32 vbo;
    u32 ebo;

    Object(std::span<f32> p_vertices, std::span<u32> p_indices);
    ~Object();
};
