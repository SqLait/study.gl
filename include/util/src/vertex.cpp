// TODO: write shit to automate the creation of objects yay
#include "data/vertex.hpp"
#include <span>

VertexAttribute gen_attribute(u32 index, u8 size, u32 type, bool normalised,
                              std::span<Attributes> attrs, usize offset) {
    u32 stride = 0;
    for (usize i = 0; i < attrs.size(); i++)
        stride += (u8)attrs.data()[i];

    return (VertexAttribute) {
        .index = index,
        .size = size,
        .type = type,
        .normalised = normalised,
        .stride = stride,
        .offset = offset
    };
}
