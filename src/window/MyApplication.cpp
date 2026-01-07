#include "MyApplication.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "asset.hpp"
#include "../utils/glError.hpp"
#include "../model/ModelManager.hpp"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

MyApplication::MyApplication():
    cam(std::make_shared<Camera>(glm::vec3(-25.0, 50.0, 0.0),
                 glm::vec3(0.0, 5.0, 0.0),
                 glm::vec3(0.0, 1.0, 0.0),
                 30.0f, 0.1f, 500.0f)),
    sun(std::make_shared<Light>(glm::vec3(10.0,60.0,20.0))),
    vertexShader(SHADER_DIR "/shader.vert", GL_VERTEX_SHADER),
    fragmentShader(SHADER_DIR "/shader.frag", GL_FRAGMENT_SHADER),
    shaderProgram({vertexShader, fragmentShader}) {

    glCheckError(__FILE__, __LINE__);

    ModelManager::loadModels();

    // map
    world = std::make_shared<World>();
}

void MyApplication::loop() {

    processInput();
    world->update(getFrameDeltaTime());

    // clear
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.3, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow();


    shaderProgram.use();

    // set matrix : projection + view
    cam->setAspect(getWindowRatio());
    projection = cam->getProjectionMatrix();
    view = cam->getViewMatrix();

    // send uniforms
    shaderProgram.setUniform("projection", projection);
    shaderProgram.setUniform("view", view);
    shaderProgram.setUniform("lightPos", sun->getPosition());

    world->draw(shaderProgram);

    shaderProgram.unuse();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void MyApplication::processInput() {

    GLFWwindow* window = getWindow();
    // exit on window close button pressed
    if (glfwWindowShouldClose(window))
        exit();

    // keyboard input
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam->handleInput('w', getFrameDeltaTime());
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam->handleInput('s', getFrameDeltaTime());
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam->handleInput('a', getFrameDeltaTime());
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam->handleInput('d', getFrameDeltaTime());

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        cam->handleInput('e', getFrameDeltaTime());
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cam->handleInput('q', getFrameDeltaTime());

    bool currPressed = false;

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        if (!keyPressed)
            world->handleInput("left");
        currPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        if (!keyPressed)
            world->handleInput("right");
        currPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        if (!keyPressed)
            world->handleInput("up");
        currPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        if (!keyPressed)
            world->handleInput("down");
        currPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (!keyPressed)
            world->handleInput("space");
        currPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        if (!keyPressed)
            world->handleInput("enter");
        currPressed = true;
    }
    keyPressed = currPressed;
}