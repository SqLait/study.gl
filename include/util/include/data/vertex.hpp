#pragma once
#include <span>
#include <types.hpp>
#include <vector>

struct VertexAttribute {
    u32 index;
    u8 size;
    u32 type;
    bool normalised;
    usize offset;
};

enum class Attributes : u8 {
    POSITION = 3,
    COLOR = 2,
    TEXTURE = 2,
};

struct Vertices {
    std::vector<f32> data;
    u32 stride;
};

void create_vertex_attr(Vertices &vertices, std::span<Attributes> attrs);

