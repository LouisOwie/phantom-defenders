#include "SpawnGate.hpp"
#include "../model/ModelManager.hpp"

SpawnGate::SpawnGate(glm::vec3 pos): Entity(ModelManager::portalModel, pos) {
}

void SpawnGate::update(float deltaTime) {
    // Spawn an enemy every spawnInterval seconds
    spawnTimer += deltaTime;
    if (spawnTimer >= spawnInterval) {
        spawnEnemy();
        spawnTimer -= spawnInterval;
    }

    for (const auto& enemy: enemies) {
        enemy->update(deltaTime);
    }

    std::erase_if(enemies,
                  [](const auto& enemy) {
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
    const auto ghost = std::make_shared<Ghost>(idCounter, NORMAL_GHOST, spawnLocation, 5.0f);
    enemies.push_back(ghost);
    idCounter++;
}
