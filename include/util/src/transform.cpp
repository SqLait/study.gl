#include "SDL3/SDL_timer.h"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float3.hpp"
#include <transform.hpp>

void Transform::rotate(f32 degree) {
    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f)); // switched the order
    transform = glm::rotate(transform, degree, glm::vec3(0.0f, 0.0f, 1.0f)); // switched the order
}

void Transform::translate(glm::vec3 translation) {
    transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
}
