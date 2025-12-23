#include "Light.hpp"

Light::Light(glm::vec3 pos) : pos(pos) {}

glm::vec3 Light::getPosition() {
    return pos;
}