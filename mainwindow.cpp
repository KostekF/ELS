#include "mainwindow.h"
#include "ui_mainwindow.h"

#include"intro.h"
#include"login.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    intro * introWindow=new intro(this);

    this->setCentralWidget(introWindow);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::showLibWindow()
{
    libWindow = new libraryWindowWidget(this);
    this->setCentralWidget(libWindow);
}

