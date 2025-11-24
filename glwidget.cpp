#include "glwidget.h"
#include <QDebug>

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent), shaderProgram(nullptr), tower(nullptr)
{
}

GLWidget::~GLWidget()
{
    makeCurrent();
    delete tower;
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

    // Create and initialize tower
    tower = new Tower();
    tower->initialize(this, shaderProgram);

    qDebug() << "OpenGL initialization complete";
}

void GLWidget::paintGL()
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use shader program
    shaderProgram->bind();

    // Render tower
    if (tower) {
        tower->render(this, shaderProgram);
    }

    shaderProgram->release();
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

