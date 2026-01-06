#include "Projectile.hpp"
#include "../model/ModelManager.hpp"

Projectile::Projectile(std::shared_ptr<Ghost> target, glm::vec3 pos): Entity(ModelManager::projectileModel, pos), target(target) {
}

void Projectile::update(float deltaTime) {
}