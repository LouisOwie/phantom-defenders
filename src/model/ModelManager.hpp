#ifndef PHANTOM_DEFENDERS_MODELMANAGER_HPP
#define PHANTOM_DEFENDERS_MODELMANAGER_HPP
#include "Model.hpp"
#include <memory>

class ModelManager {
public:
    // models
    static inline std::shared_ptr<Model> ghostModel;
    static inline std::shared_ptr<Model> mapModel;
    static inline std::shared_ptr<Model> platformModel;
    static inline std::shared_ptr<Model> selectedPlatformModel;
    static inline std::shared_ptr<Model> portalModel;
    static inline std::shared_ptr<Model> towerModel1;
    static inline std::shared_ptr<Model> towerModel2;
    static inline std::shared_ptr<Model> towerModel3;
    static inline std::shared_ptr<Model> towerModel4;

    static void loadModels();
};
#endif //PHANTOM_DEFENDERS_MODELMANAGER_HPP