#ifndef RESETPASSWORD_H
#define RESETPASSWORD_H

#include <QDialog>

namespace Ui {
class ResetPassword;
}

class ResetPassword : public QDialog
{
    Q_OBJECT

public:
    explicit ResetPassword(QWidget *parent = 0);
    ~ResetPassword();

private slots:
    void on_pushButton_resetPassword_clicked();

private:
    Ui::ResetPassword *ui;
};

#endif // RESETPASSWORD_H
