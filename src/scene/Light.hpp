#ifndef PHANTOM_DEFENDERS_LIGHT_HPP
#define PHANTOM_DEFENDERS_LIGHT_HPP
#include <glm/glm.hpp>

class Light {
public:
    Light(glm::vec3 pos);
    glm::vec3 getPosition();
private:
    glm::vec3 pos;
};
#endif //PHANTOM_DEFENDERS_LIGHT_HPP