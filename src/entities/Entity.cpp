#include "Entity.hpp"
#include <glm/gtc/matrix_transform.hpp>

Entity::Entity(std::string modelPath, glm::vec3 pos) : model(modelPath), pos(pos) {}

Model Entity::getModel() {
    return model;
}

void Entity::draw(ShaderProgram &shaderProgram) {
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, pos);
    model.draw(shaderProgram, modelMatrix);
}