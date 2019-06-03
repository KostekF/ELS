#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include<QNetworkAccessManager>
namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Register *ui;
    QNetworkAccessManager * networkManager;
    void postRegisterUser();
};

#endif // REGISTER_H
