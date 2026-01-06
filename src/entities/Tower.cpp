#include "Tower.hpp"
#include "../model/ModelManager.hpp"

Tower::Tower(glm::vec3 pos): Entity(ModelManager::towerModel1, pos), attackSpeed(1.0f), damage(10), range(15.0f) {
}

void Tower::update(float deltaTime) {
    if (target != nullptr) {
        shoot();
    }
    for (const auto& projectile : projectiles) {
        projectile->update(deltaTime);
    }
}

void Tower::draw(ShaderProgram &shaderProgram) {
    Entity::draw(shaderProgram);
    for (const auto& projectile : projectiles) {
        projectile->draw(shaderProgram);
    }
}

void Tower::shoot() {
    const auto projectile = std::make_shared<Projectile>(target, pos + glm::vec3(0.0f, 5.0f, 0.0f));
    projectiles.push_back(projectile);
}

void Tower::upgrade(int level) {
    switch (level) {
        case 2:
            model = ModelManager::towerModel2;
            damage = 12;
            attackSpeed = 1.5f;
            break;
        case 3:
            model = ModelManager::towerModel3;
            damage = 15;
            attackSpeed = 2.5f;
            break;
        case 4:
            model = ModelManager::towerModel4;
            damage = 20;
            attackSpeed = 3.0f;
            break;
        default:
            break;

    }
}
