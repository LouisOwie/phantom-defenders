#ifndef TOWER_H
#define TOWER_H
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include "lib/glm/vec3.hpp"
class Tower
{
public:
    Tower();
    ~Tower();
    void initialize(QOpenGLFunctions* gl, QOpenGLShaderProgram* shader);
    void render(QOpenGLFunctions* gl, QOpenGLShaderProgram* shader);
    void cleanup();
    void setPosition(const glm::vec3& pos) { position = pos; }
    glm::vec3 getPosition() const { return position; }
private:
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;
    glm::vec3 position;
    bool initialized;
};
#endif // TOWER_H
