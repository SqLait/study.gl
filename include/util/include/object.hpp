#pragma once
#include "data/vertex.hpp"
#include "types.hpp"
#include <span>
#include <vector>

class Object {
    Vertices vertices;
    std::vector<u32> indices;
public:
    u32 vao;
    u32 vbo;
    u32 ebo;

    Object(Vertices &p_vertices, std::span<u32> p_indices);
    ~Object();
};
