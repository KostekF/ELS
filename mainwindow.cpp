#include "mainwindow.h"
#include "ui_mainwindow.h"

#include"intro.h"
#include"login.h"
#include "QFile"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //Define stylesheets (for now only for button)
    QFile styleFile(":/stylesheets/stylesheets/qpushbutton.qss");
    styleFile.open(QFile::ReadOnly);
    QPushButton:setStyleSheet(QString::fromLatin1(styleFile.readAll()));
    styleFile.close();


    //Create welcome widget with ELS text, logo and login button
    //and set this widget as central widget
   // introWindow=new intro(this);
   // this->setCentralWidget(introWindow);


    libWindow = new libraryWindowWidget(this);
    this->setCentralWidget(libWindow);
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

