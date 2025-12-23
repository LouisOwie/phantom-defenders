#include "Ghost.hpp"
#include "../model/ModelManager.hpp"
#include <glm/gtc/matrix_transform.hpp>

Ghost::Ghost(int id, glm::vec3 pos, float speed, int health): Entity(ModelManager::ghostModel, pos), id(id), speed(speed), health(health),
    path(Path({
            glm::vec3(0.0f, 3.0f, -45.0f),
            glm::vec3(0.0f, 3.0f, 8.8f),
            glm::vec3(-17.3f, 3.0f, 8.8f),
            glm::vec3(-17.3f, 3.0f, -8.8f),
            glm::vec3(0.0f, 3.0f, -8.8f),
            glm::vec3(0.0f, 3.0f, 50.0f),
        })) {
}

void Ghost::gotHit(int damage) {
    health -= damage;
    if (health <= 0) {
        alive = false;
    }
}

void Ghost::update(float deltaTime) {
    const glm::vec3 toPathPoint = path.getPoint() - pos;
    const glm::vec3 direction = glm::normalize(toPathPoint);
    const float distance = glm::length(toPathPoint);
    pos += direction * speed * deltaTime;
    yaw = atan2(direction.x, direction.z);
    if (distance < 0.1f) {
        path.deletePoint();
    }
    if (path.isEmpty()) {
        alive = false;
    }
}

void Ghost::draw(ShaderProgram &shaderProgram) {
    auto modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, pos);
    modelMatrix = glm::rotate(modelMatrix, yaw, glm::vec3(0.0f, 1.0f, 0.0f));
    model->draw(shaderProgram, modelMatrix);
}

