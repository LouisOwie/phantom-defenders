#ifndef PHANTOM_DEFENDERS_GHOST_HPP
#define PHANTOM_DEFENDERS_GHOST_HPP
#include "Entity.hpp"
#include "Path.hpp"

// Ghost types
enum GhostType {
    MINI_GHOST = 0,
    NORMAL_GHOST = 1
};

class Ghost: public Entity {
public:
    Ghost(int id, int type, glm::vec3 pos, float speed);

    void gotHit(int damage);

    void update(float deltaTime) override;

    // getter/setter
    int getId() { return id; }
    bool isAlive() { return alive; }
private:
    int id;
    int type;
    float speed = 5.0f;
    int health;
    bool alive = true;
    Path path;
};
#endif //PHANTOM_DEFENDERS_GHOST_HPP