#ifndef PHANTOM_DEFENDERS_SPAWNGATE_HPP
#define PHANTOM_DEFENDERS_SPAWNGATE_HPP
#include <memory>
#include "Ghost.hpp"
#include "Entity.hpp"

class SpawnGate: public Entity {
public:
    SpawnGate(glm::vec3 pos);
    void update(float deltaTime) override;
    void draw(ShaderProgram& shaderProgram);

    std::vector<std::shared_ptr<Ghost>> getEnemies() { return enemies; }
private:
    std::vector<std::shared_ptr<Ghost>> enemies;
    std::vector<glm::vec3> spawnLocation = { glm::vec3(0.0f, 1.0f, -50.0f), glm::vec3(0.0f, 3.3f, -50.0f) };

    int idCounter = 0;

    int stageCounter = 0;
    float stageTimer = 0.0f;
    const float stageInterval = 20.0f;
    float spawnTimer = 0.0f;
    float spawnInterval = 5.0f;
    float spawnProbability = 0.0f;
    float enemySpeed = 4.0f;
    void spawnEnemy();
};
#endif //PHANTOM_DEFENDERS_SPAWNGATE_HPP