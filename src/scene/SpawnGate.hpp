#ifndef PHANTOM_DEFENDERS_SPAWNGATE_HPP
#define PHANTOM_DEFENDERS_SPAWNGATE_HPP
#include <memory>
#include "../entities/Ghost.hpp"

class SpawnGate {
public:
    SpawnGate();
    void updateAllEnemies(float deltaTime);
    void drawAllEnemies(ShaderProgram& shaderProgram);
private:
    Model model;
    std::vector<std::shared_ptr<Ghost>> enemies;
    glm::vec3 spawnLocation = glm::vec3(0.0f, 3.2f, -50.0f);

    int idCounter = 0;
    float spawnTimer = 0.0f;
    const float spawnInterval = 4.0f;
    void spawnEnemy();
};
#endif //PHANTOM_DEFENDERS_SPAWNGATE_HPP