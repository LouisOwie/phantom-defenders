#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "glwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create and set GLWidget as central widget
    glWidget = new GLWidget(this);
    setCentralWidget(glWidget);

    // Set window size
    resize(800, 600);
}

MainWindow::~MainWindow()
{
    delete ui;
}
