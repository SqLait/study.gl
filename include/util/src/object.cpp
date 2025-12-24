#include <object.hpp>
#include <iostream>
#include <glad/glad.h>
#include <types.hpp>

Object::Object(std::span<f32> p_vertices, std::span<u32> p_indices) :
    vertices(p_vertices.begin(), p_vertices.end()),
    indices(p_indices.begin(), p_indices.end()) {
    
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, (vertices.size() * sizeof(f32)), vertices.data(), GL_STATIC_DRAW);
    
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

Object::~Object() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}
