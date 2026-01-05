#ifndef PHANTOM_DEFENDERS_ENTITY_HPP
#define PHANTOM_DEFENDERS_ENTITY_HPP
#include "../model/Model.hpp"
#include <memory>

class Entity {
public:
    Entity(std::shared_ptr<Model> model, glm::vec3 pos = glm::vec3(0.0f));
    virtual ~Entity() = default;
    std::shared_ptr<Model> getModel();

    virtual void draw(ShaderProgram &shaderProgram);
    virtual void update(float deltaTime) = 0;

    // getter/setter
    glm::vec3 getPos() { return pos;}
    glm::mat4 getModelMatrix() { return modelMatrix; }
protected:
    std::shared_ptr<Model> model;
    glm::mat4 modelMatrix;
    glm::vec3 pos;
    float yaw = 0.0f;
};
#endif //PHANTOM_DEFENDERS_ENTITY_HPP