#ifndef MYACCSETTINGS_H
#define MYACCSETTINGS_H

#include <QDialog>
#include "Resetpassword.h"
namespace Ui {
class MyAccSettings;
}

class MyAccSettings : public QDialog
{
    Q_OBJECT

public:
    explicit MyAccSettings(QWidget *parent = nullptr);
    ~MyAccSettings();

private slots:


    void on_pushButton_clicked();

private:
    Ui::MyAccSettings *ui;

};

#endif // MYACCSETTINGS_H
