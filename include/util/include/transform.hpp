#pragma once
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float3.hpp"
#include "types.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform {
    glm::vec3 position = glm::vec3(0, 0, 0);
    glm::vec3 rotation = glm::vec3(0, 0, 0);;

public:
    glm::mat4 transform = glm::mat4(1.0f);
    void rotate(f32 degree);
    void translate(glm::vec3 translation);
};
