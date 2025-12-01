#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up = glm::vec3(0,0,1), float fov = 90.0f, float nearClip = 0.1f, float farClip = 100.0f)
    : position(position), target(target), up(up), fov(fov), nearClip(nearClip), farClip(farClip) {}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, target, up);
}

glm::mat4 Camera::getProjectionMatrix(float aspect) {
    return glm::perspective(glm::radians(fov), aspect, nearClip, farClip);
}