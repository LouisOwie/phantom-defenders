#ifndef PHANTOM_DEFENDERS_MESH_HPP
#define PHANTOM_DEFENDERS_MESH_HPP
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <assimp/scene.h>
#include "../utils/Shader.hpp"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
    aiString path;
};

class Mesh {
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void draw(glm::mat4 projection, glm::mat4 view, ShaderProgram& shaderProgram);
private:
    // mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    // shader
    GLuint vao, vbo, ibo;
    // initialize the object ( vertices and buffers )
    void createObject();
};
#endif //PHANTOM_DEFENDERS_MESH_HPP