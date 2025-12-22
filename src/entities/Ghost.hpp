#ifndef PHANTOM_DEFENDERS_GHOST_HPP
#define PHANTOM_DEFENDERS_GHOST_HPP
#include "Entity.hpp"

class Ghost: public Entity {
public:
    Ghost();
    void update(float deltaTime) override;
};
#endif //PHANTOM_DEFENDERS_GHOST_HPP