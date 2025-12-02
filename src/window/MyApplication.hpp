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
#include "../entities/Tower.hpp"
#include <vector>
#include "./Camera.hpp"

class MyApplication : public Application {
public:
    MyApplication();

protected:
    virtual void loop();

private:
    // scene entities
    Camera cam;
    std::vector<Tower> entities;

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
