#include "glwidget.h"
#include <QDebug>
GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent), tower(nullptr)
{
}
GLWidget::~GLWidget()
{
    makeCurrent();
    delete tower;
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
    // Create and initialize tower
    tower = new Tower();
    if (!tower->initialize(this)) {
        qDebug() << "Failed to initialize tower";
        delete tower;
        tower = nullptr;
        return;
    }
    qDebug() << "OpenGL initialization complete";
}
void GLWidget::paintGL()
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Render tower
    if (tower) {
        tower->render(this);
    }
}
void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}
