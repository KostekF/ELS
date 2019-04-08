#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

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

    void on_label_linkActivated(const QString &link);

private:
    Ui::login *ui;
};

#endif // LOGIN_H
