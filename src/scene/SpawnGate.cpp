#include "SpawnGate.hpp"

SpawnGate::SpawnGate(): model("../assets/portal.obj", glm::vec3(0.0f, -1.6f, -42.0f)) {
}

void SpawnGate::updateAllEnemies(float deltaTime) {
    spawnEnemy();
    for (auto enemy: enemies) {
        enemy->update(deltaTime);
    }
}

void SpawnGate::drawAllEnemies(ShaderProgram& shaderProgram) {
    model.draw(shaderProgram);
    for (auto enemy: enemies) {
        enemy->draw(shaderProgram);
    }
}

void SpawnGate::spawnEnemy() {
    auto* ghost = new Ghost(idCounter, spawnLocation);
    enemies.push_back(ghost);
    idCounter++;
}
