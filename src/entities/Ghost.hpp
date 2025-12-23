#ifndef PHANTOM_DEFENDERS_GHOST_HPP
#define PHANTOM_DEFENDERS_GHOST_HPP
#include "Entity.hpp"
#include <vector>

class Ghost: public Entity {
public:
    Ghost(int id, glm::vec3 pos);
    void update(float deltaTime) override;
    void draw(ShaderProgram &shaderProgram) override;

    // getter/setter
    int getId() { return id; }
    bool isAlive() { return alive; }
private:
    int id;
    float speed = 5.0f;
    float yaw = 0.0f;
    bool alive = true;
    std::vector<glm::vec3> path = {
        glm::vec3(0.0f, 3.0f, 8.8f),
        glm::vec3(-17.3f, 3.0f, 8.8f),
        glm::vec3(-17.3f, 3.0f, -8.8f),
        glm::vec3(0.0f, 3.0f, -8.8f),
        glm::vec3(0.0f, 3.0f, 50.0f),
    };
};
#endif //PHANTOM_DEFENDERS_GHOST_HPP