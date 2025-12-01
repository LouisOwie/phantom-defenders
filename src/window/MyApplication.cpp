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
    cam(Camera(glm::vec3(0.0, 20.0, 20.0),
                 glm::vec3(0.0, 0.0, 0.0),
                 glm::vec3(0.0, 0.0, 1.0),
                 30.0f, 0.1f, 100.0f)),
    vertexShader(SHADER_DIR "/shader.vert", GL_VERTEX_SHADER),
    fragmentShader(SHADER_DIR "/shader.frag", GL_FRAGMENT_SHADER),
    shaderProgram({vertexShader, fragmentShader}) {

    glCheckError(__FILE__, __LINE__);
    const Tower tower(shaderProgram);
    entities.resize(1, tower);
}

void MyApplication::loop() {
    // exit on window close button pressed
    if (glfwWindowShouldClose(getWindow()))
        exit();

    // set matrix : projection + view
    projection = cam.getProjectionMatrix(getWindowRatio());
    view = cam.getViewMatrix();

    // clear
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto entity: entities) {
        entity.draw(projection, view);
    }
}