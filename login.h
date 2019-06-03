#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include"Register.h"
#include"Resetpassword.h"
#include<QNetworkAccessManager>
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

signals:
    void loginSuccessful(int permission=0);




private slots:
    void on_pushButton_login_clicked();
    void on_widget_register_clicked();
    void on_widget_resetPass_clicked();

private:
    Ui::login *ui;
    Register * regDialog;
    ResetPassword * resetDialog;
    QNetworkAccessManager * networkManager;
    void checkLoginCredentials();
};

#endif // LOGIN_H
