#ifndef TOWER_H
#define TOWER_H
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <glm/glm.hpp>
#include <QString>
class Tower
{
public:
    Tower();
    ~Tower();
    bool initialize(QOpenGLFunctions* gl);
    void render(QOpenGLFunctions* gl);
    void cleanup();
    void setPosition(const glm::vec3& pos) { position = pos; }
    glm::vec3 getPosition() const { return position; }
private:
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;
    QOpenGLShaderProgram* shaderProgram;
    glm::vec3 position;
    bool initialized;
    bool loadShaders(const QString& vertexPath, const QString& fragmentPath);
};
#endif // TOWER_H
