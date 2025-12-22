#ifndef PHANTOM_DEFENDERS_ENTITY_HPP
#define PHANTOM_DEFENDERS_ENTITY_HPP
#include "Model.hpp"

class Entity {
public:
    Entity(std::string modelPath, glm::vec3 pos = glm::vec3(0.0f));
    virtual ~Entity() = default;
    Model getModel();

    void draw(ShaderProgram &shaderProgram);
    virtual void update(float deltaTime) = 0;
protected:
    Model model;
    glm::vec3 pos;
};
#endif //PHANTOM_DEFENDERS_ENTITY_HPP