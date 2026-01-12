#include "Ghost.hpp"
#include "../model/ModelManager.hpp"
#include "../scene/World.hpp"

Ghost::Ghost(const int id, const GhostType type, const glm::vec3 pos, const float speed): Entity(type == NORMAL_GHOST ? ModelManager::ghostModel : ModelManager::miniGhostModel, pos),
    id(id), type(type), speed(speed),
    path(Path({
            glm::vec3(0.0f, pos.y, -45.0f),
            glm::vec3(0.0f, pos.y, 8.8f),
            glm::vec3(-17.3f, pos.y, 8.8f),
            glm::vec3(-17.3f, pos.y, -8.8f),
            glm::vec3(0.0f, pos.y, -8.8f),
            glm::vec3(0.0f, pos.y, 50.0f),
        })) {
    health = type ? 100 : 30;
}

void Ghost::gotHit(const int damage) {
    health -= damage;
    if (health <= 0) {
        alive = false;
        World::gold += type == NORMAL_GHOST ? 15 : 5;
    }
}

void Ghost::update(const float deltaTime) {
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
        World::gameOver = true;
    }
}

