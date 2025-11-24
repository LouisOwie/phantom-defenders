#include "tower.h"
#include <QDebug>
Tower::Tower() 
    : vbo(QOpenGLBuffer::VertexBuffer), position(0.0f, 0.0f, 0.0f), initialized(false)
{
}
Tower::~Tower()
{
    cleanup();
}
void Tower::initialize(QOpenGLFunctions* gl, QOpenGLShaderProgram* shader)
{
    if (initialized) return;
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
    shader->enableAttributeArray(0);
    shader->setAttributeBuffer(0, GL_FLOAT, 0, 3, 3 * sizeof(float));
    // Unbind
    vbo.release();
    vao.release();
    initialized = true;
    qDebug() << "Tower initialized";
}
void Tower::render(QOpenGLFunctions* gl, QOpenGLShaderProgram* shader)
{
    if (!initialized) return;
    // Bind VAO and draw
    vao.bind();
    gl->glDrawArrays(GL_TRIANGLES, 0, 3);
    vao.release();
}
void Tower::cleanup()
{
    if (initialized) {
        vao.destroy();
        vbo.destroy();
        initialized = false;
    }
}
