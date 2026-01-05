#ifndef PHANTOM_DEFENDERS_PLATFORM_HPP
#define PHANTOM_DEFENDERS_PLATFORM_HPP
#include "Tower.hpp"
#include "Entity.hpp"

class Platform: public Entity {
public:
    Platform(glm::vec3 pos);

    void update(float deltaTime) override;
    void draw(ShaderProgram &shaderProgram) override;

    void select();
    void deselect();
    void upgrade();
private:
    std::shared_ptr<Tower> tower = nullptr;
    bool selected = false;
    int level = 0;
    std::vector<int> priceTable = {50, 100, 200, 300};
};
#endif //PHANTOM_DEFENDERS_PLATFORM_HPP