#include "Entity.hpp"


Entity::Entity(std::shared_ptr<Model> model, glm::vec3 pos) : model(model), pos(pos) {}

std::shared_ptr<Model> Entity::getModel() {
    return model;
}