/**
 * MyApplication.cpp
 * Contributors:
 *      * Arthur Sonzogni (author)
 * Licence:
 *      * MIT
 */
#include "MyApplication.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "asset.hpp"
#include "../utils/glError.hpp"

MyApplication::MyApplication():
    cam(Camera(glm::vec3(0.0, 5.0, -20.0),
                 glm::vec3(0.0, 5.0, 0.0),
                 glm::vec3(0.0, 1.0, 0.0),
                 30.0f, 0.1f, 100.0f)),
    sun(Light(glm::vec3(5.0,5.0,1.0))),
    vertexShader(SHADER_DIR "/shader.vert", GL_VERTEX_SHADER),
    fragmentShader(SHADER_DIR "/shader.frag", GL_FRAGMENT_SHADER),
    shaderProgram({vertexShader, fragmentShader}) {

    glCheckError(__FILE__, __LINE__);
    const Model towerModel("../assets/testTower.obj");
    entities.resize(1, towerModel);
}

void MyApplication::loop() {

    processInput(getFrameDeltaTime());

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

    for (auto entity: entities) {
        entity.draw(projection, view, shaderProgram);
    }
    shaderProgram.unuse();
}

void MyApplication::processInput(float deltaTime) {

    GLFWwindow* window = getWindow();
    // exit on window close button pressed
    if (glfwWindowShouldClose(window))
        exit();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.handleInput('w', deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.handleInput('s', deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.handleInput('a', deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam.handleInput('d', deltaTime);

}