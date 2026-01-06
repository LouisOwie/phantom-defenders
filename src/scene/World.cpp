#include "World.hpp"

#include <iostream>
#include <ostream>

#include "../model/ModelManager.hpp"

int World::gold =20000;

World::World() : Entity(ModelManager::mapModel) {
    spawnGate = std::make_shared<SpawnGate>(glm::vec3(0.0f, -1.3f, -42.0f));
    platforms.push_back(std::make_shared<Platform>(glm::vec3(-9.3f, 3.3f, -0.1f)));
    platforms.push_back(std::make_shared<Platform>(glm::vec3(9.5f, 3.3f, -0.1f)));
    platforms.push_back(std::make_shared<Platform>(glm::vec3(-9.3f, 3.3f, 19.4f)));
    platforms.push_back(std::make_shared<Platform>(glm::vec3(-9.3f, 3.3f, -19.5f)));
}

void World::draw(ShaderProgram &shaderProgram) {
    Entity::draw(shaderProgram);
    spawnGate->draw(shaderProgram);
    for (const auto& platform: platforms) {
        platform->draw(shaderProgram);
    }
}

void World::update(float deltaTime) {
    spawnGate->update(deltaTime);
    for (const auto& platform: platforms) {
        const auto tower = platform->getTower();
        if (tower != nullptr) {
            const auto enemiesInRange = getEnemiesInRange(platform->getPos(), platform->getTower()->getRange());
            if (!enemiesInRange.empty()) {
                auto enemy = enemiesInRange[0];
                for (auto const& e : enemiesInRange) {
                    if (e->getId() < enemy->getId()) {
                        enemy = e;
                    }
                }
                platform->getTower()->setTarget(enemy);
            }
            else {
                platform->getTower()->setTarget(nullptr);
            }
        }
        platform->update(deltaTime);
    }
}

void World::handleInput(std::string key) {
    for (const auto& platform: platforms) {
        platform->deselect();
    }

    if (key == "down") {
        platforms[0]->select();
        selectedPlatform = platforms[0];
    }
    if (key == "up") {
        platforms[1]->select();
        selectedPlatform = platforms[1];
    }
    if (key == "right") {
        platforms[2]->select();
        selectedPlatform = platforms[2];
    }
    if (key == "left") {
        platforms[3]->select();
        selectedPlatform = platforms[3];
    }
    if (key == "space") {
        selectedPlatform = nullptr;
    }
    if (key == "enter" && selectedPlatform) {
        selectedPlatform->upgrade();
        selectedPlatform = nullptr;
    }
}

std::vector<std::shared_ptr<Ghost>> World::getEnemiesInRange(glm::vec3 pos, float range) {
    std::vector<std::shared_ptr<Ghost>> enemiesInRange;

    std::vector<std::shared_ptr<Ghost>> enemies = spawnGate->getEnemies();
    const auto towerPos2D = glm::vec2(pos.x, pos.z);
    for (const auto& enemy : enemies) {
        const auto enemyPos2D = glm::vec2(enemy->getPos().x, enemy->getPos().z);
        const float distance = glm::length(towerPos2D - enemyPos2D);
        if (distance <= range) {
            enemiesInRange.push_back(enemy);
        }
    }
    return enemiesInRange;
}