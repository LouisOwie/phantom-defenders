#ifndef PHANTOM_DEFENDERS_TOWER_HPP
#define PHANTOM_DEFENDERS_TOWER_HPP
#include "Entity.hpp"

class Tower : public Entity {
public:
    Tower(glm::vec3 pos);

    void update(float deltaTime) override;

    void upgrade(int level);
private:
    float attackSpeed;
    int damage;
    float range;
};
#endif //PHANTOM_DEFENDERS_TOWER_HPP