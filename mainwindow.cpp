#include "mainwindow.h"
#include "ui_mainwindow.h"

#include"intro.h"
#include"login.h"
#include "QFile"
#include"Register.h"
#include"Advancedsearch.h"

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

    //just for tests, delete later
   //libWindow = new libraryWindowWidget(this);
   //this->setCentralWidget(libWindow);

    //just for tests,delete later
/*
    Register * regDialog = new Register(this);
    regDialog->setModal(true);
    regDialog->show();
    regDialog->setFixedSize(regDialog->size());
*/


     //just for tests,delete later
    Advancedsearch * searchDialog = new Advancedsearch(this);
    searchDialog->setModal(true);
    searchDialog->show();
    searchDialog->setFixedSize(searchDialog->size());


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

