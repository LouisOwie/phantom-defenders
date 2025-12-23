#include "Entity.hpp"
#include <glm/gtc/matrix_transform.hpp>


Entity::Entity(std::shared_ptr<Model> model, glm::vec3 pos) : model(model), pos(pos) {}

std::shared_ptr<Model> Entity::getModel() {
    return model;
}

void Entity::draw(ShaderProgram &shaderProgram) {
    auto modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, pos);
    modelMatrix = glm::rotate(modelMatrix, yaw, glm::vec3(0.0f, 1.0f, 0.0f));
    model->draw(shaderProgram, modelMatrix);
}