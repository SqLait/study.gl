#include <data/vertex.hpp>
#include <object.hpp>
#include <glad/glad.h>
#include <types.hpp>

Object::Object(Vertices &p_vertices, std::span<u32> p_indices) :
    vertices(std::move(p_vertices)),
    indices(p_indices.begin(), p_indices.end()) {
    
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, (vertices.data.size() * sizeof(f32)), vertices.data.data(), GL_STATIC_DRAW);
    
    Attributes attrs[] = {Attributes::POSITION, Attributes::COLOR};
    create_vertex_attr(vertices, attrs);
}

Object::~Object() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}
