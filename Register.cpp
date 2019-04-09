#include "Register.h"
#include "ui_Register.h"

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    ui->lineEdit_login->setPlaceholderText("login");
    ui->lineEdit_pass->setPlaceholderText("password");
    ui->lineEdit_mail->setPlaceholderText("e-mail");
    ui->lineEdit_name->setPlaceholderText("first name");
    ui->lineEdit_lastname->setPlaceholderText("last name");

    //Set logo img in login screen
    QPixmap pixmap(":/img/img/croppedlogo.png");
    ui->label_logoLogin->setAlignment(Qt::AlignCenter);
    ui->label_logoLogin->setPixmap(pixmap.scaled(ui->label_logoLogin->size(),Qt::KeepAspectRatio));

}

Register::~Register()
{
    delete ui;
}

void Register::on_pushButton_clicked()
{
    //TODO register user!
    this->close();
}
