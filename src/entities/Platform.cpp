#include "Platform.hpp"
#include "../model/ModelManager.hpp"
#include "../scene/World.hpp"

Platform::Platform(glm::vec3 pos): Entity(ModelManager::platformModel, pos) {
}

void Platform::update(float deltaTime) {
}

void Platform::draw(ShaderProgram &shaderProgram) {
    Entity::draw(shaderProgram);
    if (tower) {
        tower->draw(shaderProgram);
    }
}

void Platform::select() {
    model = ModelManager::selectedPlatformModel;
    selected = true;
}

void Platform::deselect() {
    model = ModelManager::platformModel;
    selected = false;
}

void Platform::upgrade() {
    if (level >=4 || World::gold < priceTable[level]) {
        return;
    }
    World::gold -= priceTable[level];
    level++;
    switch (level) {
        case 1:
            tower = std::make_shared<Tower>(pos + glm::vec3(0.0f, 0.5f, 0.0f));
            break;
        case 2:
        case 3:
        case 4:
            tower->upgrade(level);
            break;
        default:
            break;
    }
}