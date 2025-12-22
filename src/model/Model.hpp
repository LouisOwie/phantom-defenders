#ifndef PHANTOM_DEFENDERS_MODEL_HPP
#define PHANTOM_DEFENDERS_MODEL_HPP
#include <vector>
#include <string>
#include "Mesh.hpp"
#include <assimp/scene.h>


class Model {
public:
    Model(std::string path, glm::vec3 pos = glm::vec3(0.0f));
    void draw(ShaderProgram& shaderProgram, glm::mat4 modelMatrix = glm::mat4(1.0));
private:
    glm::vec3 pos;
    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(std::string path);

    void processNode(aiNode *node, const aiScene* scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

    unsigned int textureFromFile(std::string path, const std::string &directory);
};
#endif //PHANTOM_DEFENDERS_MODEL_HPP