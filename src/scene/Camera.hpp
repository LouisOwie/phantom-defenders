#ifndef PHANTOM_DEFENDERS_CAMERA_HPP
#define PHANTOM_DEFENDERS_CAMERA_HPP
#include <glm/glm.hpp>

class Camera {
public:
    // constructor
    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fov, float nearClip, float farClip);

    // get view and projection matrices
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    // process keyboard inputs
    void handleInput(char key, float deltaTime);

    void setAspect(float aspectRatio);
private:
    float aspect;
    // camera parameters
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;

    // projection parameters
    float fov;
    float nearClip;
    float farClip;
};
#endif //PHANTOM_DEFENDERS_CAMERA_HPP