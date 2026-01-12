#include "SpawnGate.hpp"
#include "../model/ModelManager.hpp"
//#include <iostream>

SpawnGate::SpawnGate(glm::vec3 pos): Entity(ModelManager::portalModel, pos) {
}

void SpawnGate::update(float deltaTime) {
    stageTimer += deltaTime;
    if (stageTimer >= stageInterval) {
        stageCounter++;
        stageTimer -= stageInterval;
        spawnInterval = 0.3f + (5.0f - 0.3f) * std::exp(-0.2f * stageCounter);
        spawnProbability = glm::min(0.0f + floor(static_cast<float>(stageCounter + 1) / 2.0f) * 0.1f, 1.0f);
        enemySpeed = glm::min(4.0f + static_cast<float>(stageCounter) * 0.1f, 6.0f);

        // Debug output
        /*
        static float totalGold = 50.0f;
        std::cout << "SpawnGate: Stage = " << stageCounter << std::endl;
        float goldInStage = 20.0f * ((spawnProbability * 15.0f + (1 - spawnProbability) * 5.0f) / spawnInterval);
        totalGold += goldInStage;
        std::cout << "gold per stage: " << goldInStage << std::endl;
        std::cout << "total gold: " << totalGold << std::endl;
        std::cout << "health per second: " << (spawnProbability * 100.0f + (1 - spawnProbability) * 30.0f) / spawnInterval << std::endl;
        std::cout << "damage per second: " << getDamage(totalGold) << std::endl;
        std::cout << "------------------------" << std::endl;
        */
    }

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
    const GhostType type = (static_cast<float>(rand()) / RAND_MAX) < spawnProbability ? NORMAL_GHOST : MINI_GHOST;
    const auto ghost = std::make_shared<Ghost>(idCounter, type, spawnLocation[type], 5.0f);
    enemies.push_back(ghost);
    idCounter++;
}

/* Debug function to calculate damage per second based on gold
float getDamage(float gold) {
    int i = 0;
    float damage = 0;
    while (gold >= 50.0f && i < 4) {
        i++;
        damage += 7.0f;
        gold -= 50.0f;
    }
    i = 0;
    while (gold >= 100.0f && i < 4) {
        i++;
        damage += 11.0f;
        gold -= 100.0f;
    }
    i = 0;
    while (gold >= 300.0f && i < 4) {
        i++;
        damage += 19.5f;
        gold -= 300.0f;
    }
    i = 0;
    while (gold >= 700.0f && i < 4) {
        i++;
        damage += 22.5f;
        gold -= 700.0f;
    }
    return damage;
}
*/
