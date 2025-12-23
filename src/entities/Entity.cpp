#include "Entity.hpp"


Entity::Entity(Model* model, glm::vec3 pos) : model(model), pos(pos) {}

Model* Entity::getModel() {
    return model;
}