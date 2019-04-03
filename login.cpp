#include "login.h"
#include "ui_login.h"
#include"QFocusEvent"
#include"QDebug"
#include "mainwindow.h"
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    ui->lineEdit_login->setPlaceholderText("login");
    ui->lineEdit_pass->setPlaceholderText("password");


    QPixmap pixmap(":/img/img/croppedlogo.png");
    int height=ui->label_logoLogin->height();
    int width=ui->label_logoLogin->width();
    ui->label_logoLogin->setAlignment(Qt::AlignCenter);
    ui->label_logoLogin->setPixmap(pixmap.scaled(ui->label_logoLogin->size(),Qt::KeepAspectRatio));


}

login::~login()
{
    delete ui;
}





void login::on_pushButton_login_clicked()
{
    QString myLogin=ui->lineEdit_login->text();
    QString myPass=ui->lineEdit_pass->text();

    //TODO: ADD crypto of password and send it to server

    //TODO: check token recived from server
    //if(login succesfull)

      //connect(this,SIGNAL(login::loginSuccessful()),MainWindow,SLOT(MainWindow::showLibWindow()));
         emit loginSuccessful();
        this->close();


}
