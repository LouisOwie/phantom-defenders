#include "tower.h"
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
Tower::Tower()
    : vbo(QOpenGLBuffer::VertexBuffer), 
      shaderProgram(nullptr),
      position(0.0f, 0.0f, 0.0f), 
      initialized(false)
{
}
Tower::~Tower()
{
    cleanup();
}
bool Tower::loadShaders(const QString& vertexPath, const QString& fragmentPath)
{
    // Create shader program
    shaderProgram = new QOpenGLShaderProgram();
    // Compile and link shaders from resource paths
    if (!shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexPath)) {
        delete shaderProgram;
        shaderProgram = nullptr;
        return false;
    }
    if (!shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentPath)) {
        delete shaderProgram;
        shaderProgram = nullptr;
        return false;
    }
    if (!shaderProgram->link()) {
        delete shaderProgram;
        shaderProgram = nullptr;
        return false;
    }
    return true;
}

bool Tower::initialize(QOpenGLFunctions* gl)
{
    if (initialized) return true;
    // Load shaders from resources (QRC)
    if (!loadShaders(":/shader/tower.vert", ":/shader/tower.frag")) {
        qDebug() << "Failed to load tower shaders";
        return false;
    }
    // Triangle vertices (placeholder for tower model)
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  // Left
         0.5f, -0.5f, 0.0f,  // Right
         0.0f,  0.5f, 0.0f   // Top
    };
    // Create and bind VAO
    vao.create();
    vao.bind();
    // Create and bind VBO
    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));
    // Set vertex attributes
    shaderProgram->bind();
    shaderProgram->enableAttributeArray(0);
    shaderProgram->setAttributeBuffer(0, GL_FLOAT, 0, 3, 3 * sizeof(float));
    shaderProgram->release();
    // Unbind
    vbo.release();
    vao.release();
    initialized = true;
    qDebug() << "Tower initialized";
    return true;
}
void Tower::render(QOpenGLFunctions* gl)
{
    if (!initialized || !shaderProgram) return;
    // Use shader program
    shaderProgram->bind();
    // Bind VAO and draw
    vao.bind();
    gl->glDrawArrays(GL_TRIANGLES, 0, 3);
    vao.release();
    shaderProgram->release();
}
void Tower::cleanup()
{
    if (initialized) {
        vao.destroy();
        vbo.destroy();
        initialized = false;
    }
    if (shaderProgram) {
        delete shaderProgram;
        shaderProgram = nullptr;
    }
}
