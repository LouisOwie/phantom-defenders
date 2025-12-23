#ifndef PHANTOM_DEFENDERS_GHOST_HPP
#define PHANTOM_DEFENDERS_GHOST_HPP
#include "Entity.hpp"
#include "../scene/Path.hpp"

class Ghost: public Entity {
public:
    Ghost(int id, glm::vec3 pos, float speed = 5.0f, int health = 3);

    void gotHit(int damage);

    void update(float deltaTime) override;
    void draw(ShaderProgram &shaderProgram) override;

    // getter/setter
    int getId() { return id; }
    bool isAlive() { return alive; }
private:
    int id;
    float speed;
    int health;
    float yaw = 0.0f;
    bool alive = true;
    Path path;
};
#endif //PHANTOM_DEFENDERS_GHOST_HPP