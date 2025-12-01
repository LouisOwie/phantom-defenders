#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fov, float nearClip, float farClip)
    : position(position), target(target), up(up), fov(fov), nearClip(nearClip), farClip(farClip) {}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, target, up);
}

glm::mat4 Camera::getProjectionMatrix(float aspect) {
    return glm::perspective(glm::radians(fov), aspect, nearClip, farClip);
}