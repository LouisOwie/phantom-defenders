#include "Tower.hpp"
#include "../model/ModelManager.hpp"

Tower::Tower(glm::vec3 pos): Entity(ModelManager::towerModel1, pos), attackSpeed(1.0f), damage(10), range(5.0f) {
}

void Tower::update(float deltaTime) {
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
