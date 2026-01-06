#include "Projectile.hpp"
#include "../model/ModelManager.hpp"

Projectile::Projectile(int damage, std::shared_ptr<Ghost> target, glm::vec3 pos): Entity(ModelManager::projectileModel, pos), target(target), damage(damage) {
}

void Projectile::update(float deltaTime) {
    const glm::vec3 direction = glm::normalize(target->getPos() - pos);
    pos += direction * 40.0f * deltaTime;

    const float distance = glm::length(target->getPos() - pos);
    if (distance < 1.0f && !hasHit) {
        hasHit = true;
        target->gotHit(damage);
    }
}