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
            position.z = glm::max(position.z - speed, -37.0f);
            target.z = glm::max(target.z - speed, -37.0f);
            break;
        case 'd':
            position.z = glm::min(position.z + speed, 37.0f);
            target.z = glm::min(target.z + speed, 37.0f);
            break;
        case 'e': {
            glm::vec3 direction = position - target;
            float radius = glm::length(direction);

            float currentPitch = asin(direction.y / radius);
            float pitchSpeed = 1.5f * deltaTime;

            float newPitch = glm::min(currentPitch + pitchSpeed, glm::radians(89.0f));

            float horizontalDist = radius * cos(newPitch);
            glm::vec3 horizontalDir = glm::normalize(glm::vec3(direction.x, 0.0f, direction.z));

            position = target + horizontalDir * horizontalDist;
            position.y = target.y + radius * sin(newPitch);
            break;
        }
        case 'q': {
            glm::vec3 direction = position - target;
            float radius = glm::length(direction);

            float currentPitch = asin(direction.y / radius);
            float pitchSpeed = 1.5f * deltaTime;

            float newPitch = glm::max(currentPitch - pitchSpeed, glm::radians(10.0f));

            float horizontalDist = radius * cos(newPitch);
            glm::vec3 horizontalDir = glm::normalize(glm::vec3(direction.x, 0.0f, direction.z));

            position = target + horizontalDir * horizontalDist;
            position.y = target.y + radius * sin(newPitch);
            break;
        }
        default:
            break;
    }
}

void Camera::setAspect(float aspectRatio) {
    aspect = aspectRatio;
}