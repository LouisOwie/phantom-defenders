#include "glwidget.h"
#include <QDebug>

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent), vbo(QOpenGLBuffer::VertexBuffer), shaderProgram(nullptr)
{
}

GLWidget::~GLWidget()
{
    makeCurrent();
    vao.destroy();
    vbo.destroy();
    delete shaderProgram;
    doneCurrent();
}

void GLWidget::initializeGL()
{
    // Initialize OpenGL functions
    initializeOpenGLFunctions();

    qDebug() << "OpenGL Version:" << (const char*)glGetString(GL_VERSION);
    qDebug() << "Renderer:" << (const char*)glGetString(GL_RENDERER);

    // Set background color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Create shader program
    shaderProgram = new QOpenGLShaderProgram(this);

    // Vertex shader
    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;

        void main()
        {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    )";

    // Fragment shader
    const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(1.0, 0.5, 0.2, 1.0);
        }
    )";

    // Compile and link shaders
    if (!shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource)) {
        qDebug() << "Vertex shader compilation failed:" << shaderProgram->log();
        return;
    }

    if (!shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource)) {
        qDebug() << "Fragment shader compilation failed:" << shaderProgram->log();
        return;
    }

    if (!shaderProgram->link()) {
        qDebug() << "Shader program linking failed:" << shaderProgram->log();
        return;
    }

    qDebug() << "Shader program created successfully";

    // Triangle vertices
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

    qDebug() << "OpenGL initialization complete";
}

void GLWidget::paintGL()
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use shader program
    shaderProgram->bind();

    // Draw triangle
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    vao.release();

    shaderProgram->release();
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

