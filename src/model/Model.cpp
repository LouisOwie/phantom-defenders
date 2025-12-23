#define STB_IMAGE_IMPLEMENTATION
#include "Model.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>
#include <filesystem>
#include <stb_image.h>

Model::Model(std::string path, glm::vec3 pos) : pos(pos) {
    loadModel(path);
}

void Model::draw(ShaderProgram &shaderProgram, glm::mat4 modelMatrix) {
    for (unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].draw(shaderProgram, modelMatrix);
}

void Model::loadModel(std::string path) {
    if (!std::filesystem::exists(path)) {
        std::cout << "FILE DOES NOT EXIST: " << std::filesystem::absolute(path) << std::endl;
    }
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 vPosition(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex.position = vPosition + pos;
        glm::vec3 normal(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        vertex.normal = normal;
        if (mesh->mTextureCoords[0]) {
            glm::vec2 texCoords(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            vertex.texCoords = texCoords;
        } else {
            vertex.texCoords = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        std::cout << "Loading materials for mesh..." << std::endl;
        // load diffuse maps
        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        std::cout << "Loaded " << diffuseMaps.size() << " diffuse textures" << std::endl;
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // load specular maps
        std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        std::cout << "Loaded " << specularMaps.size() << " specular textures" << std::endl;
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        if (diffuseMaps.empty()) {
            aiColor3D kd(0,0,0);
            if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, kd)) {
                Texture kdTexture;
                kdTexture.id = 0;
                kdTexture.type = "kd_color";
                kdTexture.path = "";
                kdTexture.color = glm::vec3(kd.r, kd.g, kd.b);
                textures.push_back(kdTexture);
            }
        }
    }
    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        Texture texture;
        texture.id = textureFromFile(str.C_Str(), directory);
        texture.type = typeName;
        texture.path = str;
        textures.push_back(texture);
    }
    return textures;
}

unsigned int Model::textureFromFile(std::string path, const std::string &directory)
{
    // load and generate the texture
    std::string filename = directory + "/" + path;
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        std::cout << "Texture loaded successfully: " << filename << " (" << width << "x" << height << ", " << nrChannels << " channels)" << std::endl;
    }
    else
    {
        std::cout << "Failed to load texture: " << filename << std::endl;
    }
    stbi_image_free(data);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
}
