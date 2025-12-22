#include "SpawnGate.hpp"

SpawnGate::SpawnGate(): model("../assets/portal.obj", glm::vec3(0.0f, -1.6f, -42.0f)) {
}

void SpawnGate::updateAllEnemies(const float deltaTime) {
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
                      return enemy->getPos().z > 50.0f;
                  });
}

void SpawnGate::drawAllEnemies(ShaderProgram& shaderProgram) {
    model.draw(shaderProgram);
    for (const auto& enemy: enemies) {
        enemy->draw(shaderProgram);
    }
}

void SpawnGate::spawnEnemy() {
    const auto ghost = std::make_shared<Ghost>(idCounter, spawnLocation);
    enemies.push_back(ghost);
    idCounter++;
}
