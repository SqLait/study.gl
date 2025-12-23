#include "SDL3/SDL_timer.h"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float3.hpp"
#include <transform.hpp>

void Transform::rotate(f32 degree, glm::vec3 axis) {
    transform = glm::rotate(transform, degree, axis); // switched the order
}

void Transform::translate(glm::vec3 translation) {
    position += translation;
    transform = glm::translate(transform, translation);
}

void Transform::set_position(glm::vec3 n_position) {
    position = n_position;
    transform = glm::translate(transform, position);
}

const glm::mat4 &Transform::get_trans_mtrx() {
    return transform;
}
