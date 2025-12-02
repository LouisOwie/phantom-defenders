#ifndef PHANTOM_DEFENDERS_TOWER_HPP
#define PHANTOM_DEFENDERS_TOWER_HPP
#include <GL/glew.h>
#include "utils/Shader.hpp"

class Tower {
 public:
    Tower(ShaderProgram& shaderProgram);
    void draw(glm::mat4 projection, glm::mat4 view);

 private:
    const int size = 100;
    // shader
    ShaderProgram& shaderProgram;
    GLuint vao, vbo, ibo;
    // initialize the object ( vertices and buffers )
    void createObject();
};
#endif //PHANTOM_DEFENDERS_TOWER_HPP