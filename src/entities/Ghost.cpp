#include "Ghost.hpp"

Ghost::Ghost(int id, glm::vec3 pos) : Entity("../assets/ghost.obj", pos), id(id) {
}

void Ghost::update(float deltaTime) {
    pos.z += deltaTime *5.0f;
}