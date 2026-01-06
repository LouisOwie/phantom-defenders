#include "Projectile.hpp"
#include "../model/ModelManager.hpp"

Projectile::Projectile(int damage, std::shared_ptr<Ghost> target, glm::vec3 pos): Entity(ModelManager::projectileModel, pos), target(target), damage(damage) {
}

void Projectile::update(float deltaTime) {
    if (!target || !target->isAlive()) {
        return;
    }

    const glm::vec3 targetPos = target->getPos();
    const glm::vec3 direction = glm::normalize(targetPos - pos);
    pos += direction * 40.0f * deltaTime;

    const float distance = glm::length(targetPos - pos);
    if (distance < 1.0f && !hasHit) {
        hasHit = true;
        target->gotHit(damage);
    }
}