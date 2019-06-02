#ifndef MYACCSETTINGS_H
#define MYACCSETTINGS_H

#include <QDialog>
#include "Resetpassword.h"
#include<QNetworkAccessManager>
#include<QJsonArray>
#include"Book.h"
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


    void on_pushButton_returnBook_clicked();

private:
    Ui::MyAccSettings *ui;
    QNetworkAccessManager * networkManager=nullptr;

    //for change loan date
    QString loanID_="";
    //for showUsersBooks()

    QJsonArray userBookList_={};
    Book book_;
    std::vector<Book> vBooks_={};
    QString finishDate_;
    std::vector<QString> vfinishDates_={};
    void changeLoanFinishDate();
    void showUsersBooks();
    void updateBookAvailability();
    void updateLoanStatus();
    void postDateAndStatus();
    void delRemoveLoan();
    void postRemoveBookFromUserList();
};

#endif // MYACCSETTINGS_H
