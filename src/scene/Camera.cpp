#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fov, float nearClip, float farClip)
    : position(position), target(target), up(up), fov(fov), nearClip(nearClip), farClip(farClip) {}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, target, up);
}

glm::mat4 Camera::getProjectionMatrix() {
    return glm::perspective(glm::radians(fov), aspect, nearClip, farClip);
}

void Camera::handleInput(char key, float deltaTime) {
    const float speed = 30.0f * deltaTime;

    switch (key) {
        case 'w':
            if (target.x + speed <= 20.0f) {
                position.x += speed;
                target.x += speed;
            }
            break;
        case 's':
            if (target.x - speed >= -12.0f) {
                position.x -= speed;
                target.x -= speed;
            }
            break;
        case 'a':
            position.z = glm::max(position.z - speed, -35.0f);
            target.z = glm::max(target.z - speed, -35.0f);
            break;
        case 'd':
            position.z = glm::min(position.z + speed, 36.0f);
            target.z = glm::min(target.z + speed, 36.0f);
            break;
        case 'e':
            adjustPitch(1.0f, deltaTime);
            break;
        case 'q':
            adjustPitch(-1.0f, deltaTime);
            break;
        default:
            break;
    }
}

void Camera::setAspect(float aspectRatio) {
    aspect = aspectRatio;
}

void Camera::adjustPitch(float pitchDelta, float deltaTime) {
    const glm::vec3 direction = position - target;
    const float radius = glm::length(direction);

    // Check if direction is valid (not zero)
    constexpr float epsilon = 1e-6f;
    if (radius < epsilon) {
        return;
    }

    const float currentPitch = asin(direction.y / radius);
    const float pitchSpeed = 1.5f * deltaTime;

    const float newPitch = glm::clamp(currentPitch + pitchDelta * pitchSpeed, glm::radians(10.0f), glm::radians(89.0f));

    const float horizontalDist = radius * cos(newPitch);
    auto horizontalDir = glm::vec3(direction.x, 0.0f, direction.z);
    
    // Check if horizontal direction is valid (not zero)
    const float horizontalLength = glm::length(horizontalDir);
    if (horizontalLength < epsilon) {
        return;
    }
    
    horizontalDir = glm::normalize(horizontalDir);

    position = target + horizontalDir * horizontalDist;
    position.y = target.y + radius * sin(newPitch);
}