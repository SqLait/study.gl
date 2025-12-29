#include "glm/ext/matrix_transform.hpp"
#include <math/gmath.hpp>
#include <camera.hpp>

constexpr f32 MIN_ZOOM = 1.0f;
constexpr f32 MAX_ZOOM = 45.0f;

extern const f32 YAW = -90.0f;
extern const f32 PITCH =  0.0f;
extern const f32 SPEED =  2.5f;
extern const f32 SENSITIVITY =  0.1f;
extern const f32 ZOOM =  45.0f;

Camera::Camera(glm::vec3 position, glm::vec3 up, glm::vec3 front,
               f32 yaw, f32 pitch, f32 speed, f32 sens, f32 zoom) {
    this->position = position;
    this->up = up;
    this->front = front;
    this->yaw = yaw;
    this->pitch = pitch;
    this->speed = speed;
    this->sensitivity = sens;
    this->zoom = zoom;
}

glm::mat4 Camera::view_matrix() {
    return glm::lookAt(position, position + front, up);
}

void Camera::zoom_in(f32 value) {
    zoom = GMath::clamp((zoom + value), MIN_ZOOM, MAX_ZOOM); 
}

void Camera::zoom_out(f32 value) {
    zoom = GMath::clamp((zoom - value), MIN_ZOOM, MAX_ZOOM); 
}

void Camera::update() {

}
