#pragma once
#include <types.hpp>

struct VertexAttribute {
    u32 index;
    u8 size;
    u32 type;
    bool normalised;
    u32 stride;
    usize offset;
};

enum class Attributes : u8 {
    POSITION = 3,
    COLOR = 3,
    TEXTURE = 2,
};
