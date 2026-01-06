#ifndef PHANTOM_DEFENDERS_TOWER_HPP
#define PHANTOM_DEFENDERS_TOWER_HPP
#include "Entity.hpp"
#include "Projectile.hpp"

class Tower : public Entity {
public:
    Tower(glm::vec3 pos);

    void update(float deltaTime) override;
    void draw(ShaderProgram &shaderProgram) override;

    void upgrade(int level);

    float getRange() { return range; }
    void setTarget(std::shared_ptr<Ghost> newTarget) { target = newTarget; }
private:
    // tower stats
    float attackSpeed;
    int damage;
    float range;

    std::shared_ptr<Ghost> target;

    std::vector<std::shared_ptr<Projectile>> projectiles;

    void shoot();
};
#endif //PHANTOM_DEFENDERS_TOWER_HPP