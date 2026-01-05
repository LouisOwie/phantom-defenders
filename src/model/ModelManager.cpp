#include "ModelManager.hpp"

void ModelManager::loadModels() {
    ghostModel = std::make_shared<Model>("../assets/ghost.obj");
    mapModel = std::make_shared<Model>("../assets/map.obj");
    platformModel = std::make_shared<Model>("../assets/platform.obj");
    selectedPlatformModel = std::make_shared<Model>("../assets/platform_selected.obj");
    portalModel = std::make_shared<Model>("../assets/portal.obj");
    towerModel1 = std::make_shared<Model>("../assets/tower1.obj");
    towerModel2 = std::make_shared<Model>("../assets/tower2.obj");
    towerModel3 = std::make_shared<Model>("../assets/tower3.obj");
    towerModel4 = std::make_shared<Model>("../assets/tower4.obj");
}