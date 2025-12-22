#include "Entity.hpp"

Entity::Entity(std::string modelPath, glm::vec3 pos) : model(modelPath, pos) {}

Model Entity::getModel() {
    return model;
}