#ifndef PHANTOM_DEFENDERS_MODELMANAGER_HPP
#define PHANTOM_DEFENDERS_MODELMANAGER_HPP
#include "Model.hpp"
#include <memory>

class ModelManager {
public:
    // models
    static inline std::shared_ptr<Model> ghostModel;

    static void loadModels();
};
#endif //PHANTOM_DEFENDERS_MODELMANAGER_HPP