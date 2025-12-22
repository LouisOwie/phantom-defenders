#include "Ghost.hpp"

Ghost::Ghost() : Entity("../assets/ghost.obj", glm::vec3(0.0f, 3.0f, -50.0f)) {
}

void Ghost::update(float deltaTime) {
    pos.z += deltaTime *5.0f;
}