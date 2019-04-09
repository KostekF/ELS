#include "Resetpassword.h"
#include "ui_Resetpassword.h"

ResetPassword::ResetPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResetPassword)
{
    ui->setupUi(this);
    ui->lineEdit_mail->setPlaceholderText("e-mail");

    //Set logo img in login screen
    QPixmap pixmap(":/img/img/croppedlogo.png");
    ui->label_logoLogin->setAlignment(Qt::AlignCenter);
    ui->label_logoLogin->setPixmap(pixmap.scaled(ui->label_logoLogin->size(),Qt::KeepAspectRatio));
}

ResetPassword::~ResetPassword()
{
    delete ui;
}

void ResetPassword::on_pushButton_resetPassword_clicked()
{
    //TODO do something when user wants to reset password
    //QString email=ui->lineEdit_mail->getText();
    this->close();
}
