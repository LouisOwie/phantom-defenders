#include "ModelManager.hpp"

void ModelManager::loadModels() {
    ghostModel = std::make_shared<Model>("../assets/ghost.obj");
    mapModel = std::make_shared<Model>("../assets/map.obj");
    platformModel = std::make_shared<Model>("../assets/platform.obj");
    selectedPlatformModel = std::make_shared<Model>("../assets/platform_selected.obj");
    portalModel = std::make_shared<Model>("../assets/portal.obj");
}