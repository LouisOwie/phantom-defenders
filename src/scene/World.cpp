#include "World.hpp"
#include "../model/ModelManager.hpp"

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
}