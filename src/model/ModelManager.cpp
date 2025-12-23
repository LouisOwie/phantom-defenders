#include "ModelManager.hpp"

void ModelManager::loadModels() {
    ghostModel = std::make_shared<Model>("../assets/ghost.obj");
}