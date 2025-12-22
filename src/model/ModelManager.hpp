#ifndef PHANTOM_DEFENDERS_MODELMANAGER_HPP
#define PHANTOM_DEFENDERS_MODELMANAGER_HPP
#include "Model.hpp"

class ModelManager {
public:
    // models
    static inline Model* ghostModel;

    static void loadModels();
};
#endif //PHANTOM_DEFENDERS_MODELMANAGER_HPP