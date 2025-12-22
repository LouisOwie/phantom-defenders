/**
 * MyApplication.hpp skeleton
 * Contributors:
 *      * Arthur Sonzogni
 * Licence:
 *      * MIT
 */

#ifndef OPENGL_CMAKE_SKELETON_MYAPPLICATION
#define OPENGL_CMAKE_SKELETON_MYAPPLICATION

#include "Application.hpp"
#include "../utils/Shader.hpp"
#include "../entities/Model.hpp"
#include "../entities/Entity.hpp"
#include <vector>
#include "../entities/Camera.hpp"
#include "../entities/Light.hpp"

class MyApplication : public Application {
public:
    MyApplication();

protected:
    virtual void loop();

private:
    // scene entities
    Camera cam;
    Light sun;
    std::vector<Model> mapModels;
    std::vector<Entity> entities;

    // shader
    Shader vertexShader;
    Shader fragmentShader;
    ShaderProgram shaderProgram;

    // shader matrix uniform
    glm::mat4 projection = glm::mat4(1.0);
    glm::mat4 view = glm::mat4(1.0);

    // input processing
    void processInput(float deltaTime);
};

#endif  // OPENGL_CMAKE_SKELETON_MYAPPLICATION
