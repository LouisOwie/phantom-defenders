#include "Platform.hpp"
#include "../model/ModelManager.hpp"

Platform::Platform(glm::vec3 pos): Entity(ModelManager::platformModel, pos) {
}

void Platform::update(float deltaTime) {
}
