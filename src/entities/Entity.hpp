#ifndef PHANTOM_DEFENDERS_ENTITY_HPP
#define PHANTOM_DEFENDERS_ENTITY_HPP
#include "Model.hpp"

class Entity {
public:
    Entity(std::string modelPath, glm::vec3 pos = glm::vec3(0.0f));
    Model getModel();
private:
    Model model;
};
#endif //PHANTOM_DEFENDERS_ENTITY_HPP