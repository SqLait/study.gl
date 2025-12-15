#include <object.hpp>
#include <iostream>

Object::Object(std::span<f32> p_vertices, std::span<u32> p_indices) :
    vertices(p_vertices.begin(), p_vertices.end()),
    indices(p_indices.begin(), p_indices.end())
{}
