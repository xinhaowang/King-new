#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setBackground();
}

//set the background of the main window
void MainWindow::setBackground()
{
    ui->centralWidget->setStyleSheet("border-image: url(:/background/image/background/background.jpg)");
}

MainWindow::~MainWindow()
{
    delete ui;
}
