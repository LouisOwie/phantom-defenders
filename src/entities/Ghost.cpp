#include "Ghost.hpp"
#include "../model/ModelManager.hpp"
#include <glm/gtc/matrix_transform.hpp>

Ghost::Ghost(int id, glm::vec3 pos) : Entity(ModelManager::ghostModel, pos), id(id) {
}

void Ghost::update(float deltaTime) {
    const glm::vec3 toPathPoint = path[0] - pos;
    const glm::vec3 direction = glm::normalize(toPathPoint);
    const float distance = glm::length(toPathPoint);
    pos += direction * speed * deltaTime;
    yaw = atan2(direction.x, direction.z);
    if (distance < 0.1f) {
        pos = path[0];
        path.erase(path.begin());
    }
    if (path.empty()) {
        alive = false;
    }
}

void Ghost::draw(ShaderProgram &shaderProgram) {
    auto modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, pos);
    modelMatrix = glm::rotate(modelMatrix, yaw, glm::vec3(0.0f, 1.0f, 0.0f));
    model->draw(shaderProgram, modelMatrix);
}

