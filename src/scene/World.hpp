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

    void handleInput(std::string key);

    static int gold;
    static bool gameOver;
private:
    std::shared_ptr<Model> exitGate;
    std::shared_ptr<SpawnGate> spawnGate;
    std::vector<std::shared_ptr<Platform>> platforms;
    std::shared_ptr<Platform> selectedPlatform;

    std::vector<std::shared_ptr<Ghost>> getEnemiesInRange(glm::vec3 pos, float range);
};
#endif //PHANTOM_DEFENDERS_WORLD_HPP