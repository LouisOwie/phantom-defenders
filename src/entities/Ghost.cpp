#include "Ghost.hpp"
#include "../model/ModelManager.hpp"

Ghost::Ghost(int id, glm::vec3 pos) : Entity(ModelManager::ghostModel, pos), id(id) {
}

void Ghost::update(float deltaTime) {
    pos.z += deltaTime *5.0f;
}