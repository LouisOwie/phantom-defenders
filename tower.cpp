#include "tower.h"
#include <QDebug>
#include <QFile>
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
    // Read vertex shader
    QFile vertFile(vertexPath);
    if (!vertFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open vertex shader:" << vertexPath;
        return false;
    }
    QString vertexShaderSource = vertFile.readAll();
    vertFile.close();
    // Read fragment shader
    QFile fragFile(fragmentPath);
    if (!fragFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open fragment shader:" << fragmentPath;
        return false;
    }
    QString fragmentShaderSource = fragFile.readAll();
    fragFile.close();
    // Create shader program
    shaderProgram = new QOpenGLShaderProgram();
    // Compile and link shaders
    if (!shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource)) {
        qDebug() << "Vertex shader compilation failed:" << shaderProgram->log();
        delete shaderProgram;
        shaderProgram = nullptr;
        return false;
    }
    if (!shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource)) {
        qDebug() << "Fragment shader compilation failed:" << shaderProgram->log();
        delete shaderProgram;
        shaderProgram = nullptr;
        return false;
    }
    if (!shaderProgram->link()) {
        qDebug() << "Shader program linking failed:" << shaderProgram->log();
        delete shaderProgram;
        shaderProgram = nullptr;
        return false;
    }
    qDebug() << "Tower shaders loaded successfully from" << vertexPath << "and" << fragmentPath;
    return true;
}
bool Tower::initialize(QOpenGLFunctions* gl)
{
    if (initialized) return true;
    // Load shaders
    if (!loadShaders("shader/tower.vert", "shader/tower.frag")) {
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
    shaderProgram->enableAttributeArray(0);
    shaderProgram->setAttributeBuffer(0, GL_FLOAT, 0, 3, 3 * sizeof(float));
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
