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
    ui->lineEdit_pass->setPlaceholderText("hasło");


    QFont font( "Ubuntu", 8,QFont::Cursive);
    ui->widget_resetPass->setFont(font);
    ui->widget_resetPass->setText("Zapomniałeś hasła?");

    ui->widget_register->setFont(font);
    ui->widget_register->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->widget_register->setText("Zarejestruj się");



    //Set logo img in login screen
    QPixmap pixmap(":/img/img/croppedlogo.png");
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


     emit loginSuccessful();
     this->close();


}




void login::on_widget_register_clicked()
{
    regDialog = new Register(this);
    regDialog->setModal(true);
    regDialog->show();
    regDialog->setFixedSize(regDialog->size());
}

void login::on_widget_resetPass_clicked()
{
    resetDialog = new ResetPassword(this);
    resetDialog->setModal(true);
    resetDialog->show();
    resetDialog->setFixedSize(resetDialog->size());
}
