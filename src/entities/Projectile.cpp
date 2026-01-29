#include "Projectile.hpp"
#include "../model/ModelManager.hpp"

Projectile::Projectile(const int damage, const std::shared_ptr<Ghost> &target, const glm::vec3 pos): Entity(ModelManager::projectileModel, pos), target(target), damage(damage) {
}

void Projectile::update(const float deltaTime) {
    if (!target || !target->isAlive()) {
        return;
    }

    const glm::vec3 targetPos = target->getPos();
    const glm::vec3 direction = glm::normalize(targetPos - pos);
    pos += direction * 40.0f * deltaTime;

    const float distance = glm::length(targetPos - pos);
    // Check for hit
    if (distance < 1.0f && !hasHit) {
        hasHit = true;
        target->gotHit(damage);
    }
}