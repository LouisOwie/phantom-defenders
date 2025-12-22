#include "MyApplication.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "asset.hpp"
#include "../utils/glError.hpp"
#include "../entities/Ghost.hpp"

MyApplication::MyApplication():
    cam(Camera(glm::vec3(-25.0, 50.0, 0.0),
                 glm::vec3(0.0, 5.0, 0.0),
                 glm::vec3(0.0, 1.0, 0.0),
                 30.0f, 0.1f, 500.0f)),
    sun(Light(glm::vec3(10.0,60.0,20.0))),
    vertexShader(SHADER_DIR "/shader.vert", GL_VERTEX_SHADER),
    fragmentShader(SHADER_DIR "/shader.frag", GL_FRAGMENT_SHADER),
    shaderProgram({vertexShader, fragmentShader}) {

    glCheckError(__FILE__, __LINE__);
    // map
    const Model towerScene("../assets/map.obj");
    mapModels.push_back(towerScene);
    //const Model testTower("../assets/testTower.obj", glm::vec3(-7.8f, 3.3f, 0.0f));
    //entities.push_back(testTower);

}

/*
 *tower positions::
 *vec3(-7.8f, 3.3f, 0.0f)
 *vec3(11.0f, 3.3f, -0.3f)
 *vec3(-7.8f, 3.3f, 19.4f)
 *vec3(-7.8f, 3.3f, -19.5f)
*/

void MyApplication::loop() {

    processInput();
    animate();

    // clear
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.3, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram.use();

    // set matrix : projection + view
    projection = cam.getProjectionMatrix(getWindowRatio());
    view = cam.getViewMatrix();

    // send uniforms
    shaderProgram.setUniform("projection", projection);
    shaderProgram.setUniform("view", view);
    shaderProgram.setUniform("lightPos", sun.getPosition());

    for (auto entity: mapModels) {
        entity.draw(shaderProgram);
    }
    spawnGate.drawAllEnemies(shaderProgram);
    shaderProgram.unuse();
}

void MyApplication::animate() {
    spawnGate.updateAllEnemies(getFrameDeltaTime());
}

void MyApplication::processInput() {

    GLFWwindow* window = getWindow();
    // exit on window close button pressed
    if (glfwWindowShouldClose(window))
        exit();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.handleInput('w', getFrameDeltaTime());
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.handleInput('s', getFrameDeltaTime());
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.handleInput('a', getFrameDeltaTime());
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam.handleInput('d', getFrameDeltaTime());

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        cam.handleInput('f', getFrameDeltaTime());
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        cam.handleInput('k', getFrameDeltaTime());
}