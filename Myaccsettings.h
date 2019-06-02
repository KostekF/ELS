#ifndef MYACCSETTINGS_H
#define MYACCSETTINGS_H

#include <QDialog>
#include "Resetpassword.h"
#include<QNetworkAccessManager>
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

    void on_pushButton_delBook_clicked();

    void on_pushButton_addBook_clicked();



    void on_pushButton_editBook_clicked();


    void on_pushButton_changeLoanDate_clicked();

private:
    Ui::MyAccSettings *ui;
    QNetworkAccessManager * networkManager=nullptr;

    //for change loan date
    QString loanID_="";
    void changeLoanFinishDate();
};

#endif // MYACCSETTINGS_H
