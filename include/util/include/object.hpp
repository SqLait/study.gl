#pragma once
#include "types.hpp"
#include <span>
#include <vector>

class Object {
public:
    std::vector<f32> vertices;
    std::vector<u32> indices;

    Object(std::span<f32> p_vertices, std::span<u32> p_indices);
};
