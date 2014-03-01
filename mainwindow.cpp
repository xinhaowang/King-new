#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setBackground();
    this->setWindowTitle("King and Thing");

    //set up the player's rack
    Things_rack = new MapWidget(this);
    Things_rack->init();
    Things_rack->setFixedSize(500, 240);
    Things_rack->move(700, 520);

    //set up the test widget
    MapWidget *testwidget = new MapWidget(this);
    testwidget->setFixedSize(500, 240);
    testwidget->move(700, 100);
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
