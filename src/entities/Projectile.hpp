#ifndef PHANTOM_DEFENDERS_PROJECTILE_HPP
#define PHANTOM_DEFENDERS_PROJECTILE_HPP
#include "Entity.hpp"
#include "Ghost.hpp"

class Projectile : public Entity {
public:
    Projectile(int damage, std::shared_ptr<Ghost> target, glm::vec3 pos);

    void update(float deltaTime) override;

    std::shared_ptr<Ghost> getTarget() { return target; }
    bool hasHitTarget() { return hasHit; }
private:
    std::shared_ptr<Ghost> target;
    int damage;
    bool hasHit = false;
};
#endif //PHANTOM_DEFENDERS_PROJECTILE_HPP