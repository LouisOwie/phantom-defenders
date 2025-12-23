#ifndef PHANTOM_DEFENDERS_WORLD_HPP
#define PHANTOM_DEFENDERS_WORLD_HPP
#include <memory>
#include "../model/Model.hpp"
#include "../entities/SpawnGate.hpp"
#include "../entities/Platform.hpp"

class World: public Entity {
public:
    World();

    void update(float deltaTime) override;
    void draw(ShaderProgram &shaderProgram) override;
private:
    std::shared_ptr<SpawnGate> spawnGate;
    std::vector<std::shared_ptr<Platform>> platforms;
};
#endif //PHANTOM_DEFENDERS_WORLD_HPP