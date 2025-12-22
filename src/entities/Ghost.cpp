#include "Ghost.hpp"

Ghost::Ghost() : model("../assets/ghost.obj", glm::vec3(0.0f, 3.0f, -50.0f)) {}

Model Ghost::getModel() {
    return model;
}