#ifndef PHANTOM_DEFENDERS_PLATFORM_HPP
#define PHANTOM_DEFENDERS_PLATFORM_HPP
#include "Entity.hpp"

class Platform: public Entity {
public:
    Platform(glm::vec3 pos);

    void update(float deltaTime) override;
private:
    bool selected = false;

};
#endif //PHANTOM_DEFENDERS_PLATFORM_HPP