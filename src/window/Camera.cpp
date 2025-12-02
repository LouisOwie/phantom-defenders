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
    // Calculate forward and right vectors ( not used rn )
    //glm::vec3 forward = glm::normalize(target - position);
    //glm::vec3 right = glm::normalize(glm::cross(forward, up));

    switch (key) {
        case 'w':
            position.y -= speed;
            target.y -= speed;
            break;
        case 's':
            position.y += speed;
            target.y += speed;
            break;
        case 'a':
            position.x += speed;
            target.x += speed;
            break;
        case 'd':
            position.x -= speed;
            target.x -= speed;
            break;
        default:
            break;
    }
}