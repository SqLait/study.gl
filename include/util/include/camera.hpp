#pragma once
#include <types.hpp>
#include <glm/glm.hpp>

extern const f32 YAW;
extern const f32 PITCH;
extern const f32 SPEED;
extern const f32 SENSITIVITY;
extern const f32 ZOOM;

class Camera {
    f32 yaw = 0;
    f32 pitch = 0;
    f32 speed = 0;
    f32 sensitivity = 0;
    f32 zoom = 0;

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;

public:
    Camera(glm::vec3 position = glm::vec3(0, 0, 0),
           glm::vec3 up = glm::vec3(0, 1, 0),
           glm::vec3 front = glm::vec3(0, 0, -1), f32 yaw = YAW,
           f32 pitch = PITCH, f32 speed = SPEED, f32 sens = SENSITIVITY,
           f32 zoom = ZOOM);

    glm::mat4 view_matrix();
    void zoom_in(f32 value);
    void zoom_out(f32 value);

private:
    void update();
};
