#ifndef PHANTOM_DEFENDERS_GHOST_HPP
#define PHANTOM_DEFENDERS_GHOST_HPP
#include "Entity.hpp"

class Ghost: public Entity {
public:
    Ghost(int id, glm::vec3 pos);
    void update(float deltaTime) override;

    // getter/setter
    int getId() { return id;}
private:
    int id;
};
#endif //PHANTOM_DEFENDERS_GHOST_HPP