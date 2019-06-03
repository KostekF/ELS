#include "intro.h"
#include "ui_intro.h"
#include"QFile"
#include "QPixmap"
#include"QDebug"
#include"login.h"
#include"mainwindow.h"
intro::intro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::intro)
{
    ui->setupUi(this);



    //Create logo image
    QPixmap pixmap(":/img/img/logo.png");
    ui->label_logoPhoto->setAlignment(Qt::AlignCenter);
   // qDebug()<<ui->label_logoPhoto->size();
    ui->label_logoPhoto->setPixmap(pixmap.scaled(ui->label_logoPhoto->size(),Qt::KeepAspectRatio));



}

intro::~intro()
{
    delete ui;
}

void intro::on_pushButton_clicked()
{
    //create login dialog
    logDialog = new login(this);
    logDialog->setModal(true);
    logDialog->show();
    logDialog->setFixedSize(logDialog->size());

    //connect successful login with hiding intro widget and showing library widget from mainwindow class
    connect(logDialog,SIGNAL(loginSuccessful()),parent(),SLOT(showLibWindow()));


}
