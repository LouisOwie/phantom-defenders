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
private:
    std::vector<std::shared_ptr<Ghost>> enemies;
    glm::vec3 spawnLocation = glm::vec3(0.0f, 3.3f, -50.0f);

    int idCounter = 0;
    float spawnTimer = 0.0f;
    const float spawnInterval = 4.0f;
    void spawnEnemy();
};
#endif //PHANTOM_DEFENDERS_SPAWNGATE_HPP