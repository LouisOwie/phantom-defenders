/**
 * Application.hpp
 * Contributors:
 *      * Arthur Sonzogni (author)
 * Licence:
 *      * MIT
 */

#include "Application.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

using namespace std;

Application* currentApplication = NULL;

Application& Application::getInstance() {
  if (currentApplication)
    return *currentApplication;
  else
    throw std::runtime_error("There is no current Application");
}

Application::Application()
    : state(stateReady), width(1280), height(720), title("Application") {
  currentApplication = this;

  cout << "[Info] GLFW initialisation" << endl;

  // initialize the GLFW library
  if (!glfwInit()) {
    throw std::runtime_error("Couldn't init GLFW");
  }

  // setting the opengl version
  int major = 4;
  int minor = 6;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // create the window
  const float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());

  window = glfwCreateWindow(
    static_cast<int>(static_cast<float>(width) * main_scale),
    static_cast<int>(static_cast<float>(height) * main_scale),
    title.c_str(),
    nullptr,
    nullptr);

  if (!window) {
    glfwTerminate();
    throw std::runtime_error("Couldn't create a window");
  }

  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  GLenum err = glewInit();

  if (err != GLEW_OK) {
    glfwTerminate();
    throw std::runtime_error(string("Could initialize GLEW, error = ") +
                             (const char*)glewGetErrorString(err));
  }

  // get version info
  const GLubyte* renderer = glGetString(GL_RENDERER);
  const GLubyte* version = glGetString(GL_VERSION);
  cout << "Renderer: " << renderer << endl;
  cout << "OpenGL version supported " << version << endl;

  // opengl configuration
  glEnable(GL_DEPTH_TEST);  // enable depth-testing
  glDepthFunc(GL_LESS);  // depth-testing interprets a smaller value as "closer"

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsLight();

  // Setup scaling
  ImGuiStyle& style = ImGui::GetStyle();
  style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
  style.FontScaleDpi = main_scale;        // Set initial font scale. (using io.ConfigDpiScaleFonts=true makes this unnecessary. We leave both here for documentation purpose)

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init();
}

GLFWwindow* Application::getWindow() const {
  return window;
}

void Application::exit() {
  state = stateExit;
}

float Application::getFrameDeltaTime() const {
  return deltaTime;
}

float Application::getTime() const {
  return time;
}

void Application::run() {
  state = stateRun;

  // Make the window's context current
  glfwMakeContextCurrent(window);

  time = glfwGetTime();

  while (state == stateRun && !glfwWindowShouldClose(window)) {
      glfwPollEvents();

      // if window minimized -> skip
      if (glfwGetWindowAttrib(window, GLFW_ICONIFIED)) {
          continue;
      }

      // compute new time and delta time
      float t = glfwGetTime();
      deltaTime = t - time;
      time = t;
      // Cap deltaTime to 60 FPS
      constexpr float maxDeltaTime = 1.0f / 60.0f;
      if (deltaTime > maxDeltaTime) {
        deltaTime = maxDeltaTime;
      }

      // get frame buffer dimensions
      int fbw, fbh;
      glfwGetFramebufferSize(window, &fbw, &fbh);

      if (fbw == 0 || fbh == 0) {
          continue;
      }

      // set viewport
      glViewport(0, 0, fbw, fbh);

      // execute loop
      loop();

      // Swap Front and Back buffers (double buffering)
      glfwSwapBuffers(window);
  }

  glfwTerminate();
}

void Application::loop() {
  cout << "[INFO] : loop" << endl;
}

int Application::getWidth() {
  return width;
}

int Application::getHeight() {
  return height;
}

float Application::getWindowRatio() {
  return float(width) / float(height);
}

bool Application::windowDimensionChanged() {
  return dimensionChanged;
}
