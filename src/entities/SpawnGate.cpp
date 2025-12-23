#include "SpawnGate.hpp"
#include "../model/ModelManager.hpp"

SpawnGate::SpawnGate(): Entity(ModelManager::portalModel) {
}

void SpawnGate::update(float deltaTime) {
    // Spawn an enemy every 2 seconds
    spawnTimer += deltaTime;
    if (spawnTimer >= spawnInterval) {
        spawnEnemy();
        spawnTimer -= spawnInterval;
    }

    for (const auto& enemy: enemies) {
        enemy->update(deltaTime);
    }

    std::erase_if(enemies,
                  [](const std::shared_ptr<Ghost>& enemy) {
                      return !enemy->isAlive();
                  });
}

void SpawnGate::draw(ShaderProgram& shaderProgram) {
    Entity::draw(shaderProgram);
    for (const auto& enemy: enemies) {
        enemy->draw(shaderProgram);
    }
}

void SpawnGate::spawnEnemy() {
    const auto ghost = std::make_shared<Ghost>(idCounter, spawnLocation);
    enemies.push_back(ghost);
    idCounter++;
}
