#pragma once
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float3.hpp"
#include "types.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform {
    glm::vec3 position = glm::vec3(0, 0, 0);
    glm::vec3 rotation = glm::vec3(0, 0, 0);;
    glm::vec3 origin = glm::vec3(0, 0, 0);
    glm::vec3 scale = glm::vec3(1, 1, 1);
    glm::mat4 transform = glm::mat4(1.0f);
public:
    void rotate(f32 degree, glm::vec3 axis);
    void translate(glm::vec3 translation);
    void set_position(glm::vec3 n_position);
    const glm::mat4 &get_trans_mtrx();
};
