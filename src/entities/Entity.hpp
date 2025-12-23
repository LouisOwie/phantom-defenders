#ifndef PHANTOM_DEFENDERS_ENTITY_HPP
#define PHANTOM_DEFENDERS_ENTITY_HPP
#include "../model/Model.hpp"

class Entity {
public:
    Entity(Model* model, glm::vec3 pos = glm::vec3(0.0f));
    virtual ~Entity() = default;
    Model* getModel();

    virtual void draw(ShaderProgram &shaderProgram) = 0;
    virtual void update(float deltaTime) = 0;

    // getter/setter
    glm::vec3 getPos() { return pos;}
protected:
    Model* model;
    glm::vec3 pos;
};
#endif //PHANTOM_DEFENDERS_ENTITY_HPP