#include "Mesh.hpp"
#include "../utils/glError.hpp"
#include <iostream>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
    : vertices(vertices),
    indices(indices),
    textures(textures) {

    createObject();
}

void Mesh::draw(glm::mat4 projection, glm::mat4 view, ShaderProgram &shaderProgram) {
    shaderProgram.use();

    // send uniforms
    shaderProgram.setUniform("projection", projection);
    shaderProgram.setUniform("view", view);

    // bind textures
    bool hasTexture = false;
    bool hasSpecularTexture = false;
    unsigned int diffuseNr = 0;
    unsigned int specularNr = 0;

    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
        if (textures[i].type == "texture_diffuse") {
            shaderProgram.setUniform("texture_diffuse", static_cast<int>(diffuseNr));
            hasTexture = true;
            diffuseNr++;
        }
        else if (textures[i].type == "texture_specular") {
            shaderProgram.setUniform("texture_specular", static_cast<int>(specularNr + 1));
            hasSpecularTexture = true;
            specularNr++;
        }
    }
    shaderProgram.setUniform("hasTexture", hasTexture);
    shaderProgram.setUniform("hasSpecularTexture", hasSpecularTexture);

    if (!hasTexture) {
        std::cout << "Warning: No diffuse texture bound for this mesh!" << std::endl;
    }

    glCheckError(__FILE__, __LINE__);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glCheckError(__FILE__, __LINE__);
    glDrawElements(GL_TRIANGLES,         // mode
                   indices.size(),       // count
                   GL_UNSIGNED_INT,      // type
                   NULL                  // element array buffer offset
    );

    glBindVertexArray(0);

    // unbind textures
    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    shaderProgram.unuse();
}

void Mesh::createObject() {

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

    glBindVertexArray(0);
}