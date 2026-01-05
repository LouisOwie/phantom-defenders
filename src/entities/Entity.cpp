#include "Entity.hpp"
#include <glm/gtc/matrix_transform.hpp>


Entity::Entity(std::shared_ptr<Model> model, glm::vec3 pos) : model(model), modelMatrix(glm::mat4(1.0)), pos(pos) {}

std::shared_ptr<Model> Entity::getModel() {
    return model;
}

void Entity::draw(ShaderProgram &shaderProgram) {
    auto transform = glm::mat4(1.0f);
    transform = glm::translate(transform, pos);
    transform = glm::rotate(transform, yaw, glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = transform;
    model->draw(shaderProgram, modelMatrix);
}