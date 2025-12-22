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

void Camera::handleInput(char key, float deltaTime) {
    float speed = 30.0f * deltaTime;

    switch (key) {
        case 'w':
            position.x += speed;
            target.x += speed;
            break;
        case 's':
            position.x -= speed;
            target.x -= speed;
            break;
        case 'a':
            position.z -= speed;
            target.z -= speed;
            break;
        case 'd':
            position.z += speed;
            target.z += speed;
            break;
        case 'f':
            position.y = 12.0f;
            break;
        case 'k':
            position.y = 50.0f;
            break;
        default:
            break;
    }
}