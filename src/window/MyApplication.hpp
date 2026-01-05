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
#include "../model/Model.hpp"
#include "../scene/Camera.hpp"
#include "../scene/Light.hpp"
#include "scene/World.hpp"

class MyApplication : public Application {
public:
    MyApplication();

protected:
    virtual void loop();

private:
    // scene entities
    std::shared_ptr<Camera> cam;
    std::shared_ptr<Light> sun;
    std::shared_ptr<World> world;

    // shader
    Shader vertexShader;
    Shader fragmentShader;
    ShaderProgram shaderProgram;

    // shader matrix uniform
    glm::mat4 projection = glm::mat4(1.0);
    glm::mat4 view = glm::mat4(1.0);

    // input processing
    bool keyPressed = false;
    void processInput();
};

#endif  // OPENGL_CMAKE_SKELETON_MYAPPLICATION
