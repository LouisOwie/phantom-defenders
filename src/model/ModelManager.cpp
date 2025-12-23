#include "ModelManager.hpp"

void ModelManager::loadModels() {
    ghostModel = std::make_shared<Model>("../assets/ghost.obj");
    platformModel = std::make_shared<Model>("../assets/platform.obj");
    selectedPlatformModel = std::make_shared<Model>("../assets/platform_selected.obj");
    portalModel = std::make_shared<Model>("../assets/portal.obj", glm::vec3(0.0f, -1.3f, -42.0f));
}