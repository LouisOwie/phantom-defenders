#ifndef PHANTOM_DEFENDERS_PROJECTILE_HPP
#define PHANTOM_DEFENDERS_PROJECTILE_HPP
#include "Entity.hpp"
#include "Ghost.hpp"

class Projectile : public Entity {
public:
    Projectile(std::shared_ptr<Ghost> target, glm::vec3 pos);

    void update(float deltaTime) override;
private:
    std::shared_ptr<Ghost> target;
};
#endif //PHANTOM_DEFENDERS_PROJECTILE_HPP