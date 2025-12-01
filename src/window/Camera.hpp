#ifndef PHANTOM_DEFENDERS_CAMERA_HPP
#define PHANTOM_DEFENDERS_CAMERA_HPP
#include <glm/glm.hpp>

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fov, float nearClip, float farClip);
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix(float aspect);
    void handleInput(char key, float deltaTime);
private:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;

    float fov;
    float nearClip;
    float farClip;
};
#endif //PHANTOM_DEFENDERS_CAMERA_HPP