#include "data/vertex.hpp"
#include <glad/glad.h>
#include <span>

static void setup_attribute(Vertices &vertices, VertexAttribute &attr) {
    glVertexAttribPointer(attr.index, attr.size, attr.type,
                          attr.normalised, vertices.stride,
                          (void*)(attr.offset));
    glEnableVertexAttribArray(attr.index);
}

void create_vertex_attr(Vertices &vertices, std::span<Attributes> attrs) {
    for (u32 i = 0; i < attrs.size(); i++) {
        vertices.stride += static_cast<u32>(attrs.data()[i]);
    }
    vertices.stride *= sizeof(f32);

    usize offset = 0;
    for (u32 i = 0; i < attrs.size(); i++) {
        VertexAttribute attrib = {
            .index = i,
            .size = (u8)attrs.data()[i],
            .type = GL_FLOAT,
            .normalised = false,
            .offset = offset
        };
        setup_attribute(vertices, attrib);
        offset += (u8)attrs.data()[i] * sizeof(f32);
    }
}
