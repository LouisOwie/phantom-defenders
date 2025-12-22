#ifndef PHANTOM_DEFENDERS_SPAWNGATE_HPP
#define PHANTOM_DEFENDERS_SPAWNGATE_HPP
#include "../entities/Ghost.hpp"

class SpawnGate {
public:
    SpawnGate();
    void updateAllEnemies(float deltaTime);
    void drawAllEnemies(ShaderProgram& shaderProgram);
private:
    Model model;
    std::vector<Ghost*> enemies;
    glm::vec3 spawnLocation = glm::vec3(0.0f, 3.0f, -50.0f);

    int idCounter = 0;
    void spawnEnemy();
};
#endif //PHANTOM_DEFENDERS_SPAWNGATE_HPP