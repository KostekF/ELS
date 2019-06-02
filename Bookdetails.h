#ifndef BOOKDETAILS_H
#define BOOKDETAILS_H

#include <QDialog>
#include"Book.h"
#include<QNetworkAccessManager>
#include<QJsonArray>
namespace Ui {
class BookDetails;
}

class BookDetails : public QDialog
{
    Q_OBJECT

public:
    explicit BookDetails(Book book,QWidget *parent = 0);
    ~BookDetails();

private:
    Ui::BookDetails *ui;
    Book book_;
    QNetworkAccessManager * networkManager=nullptr;


    void createLoan();
    void updateBookAvailability();
    void updateUserBooklist();  //get books borrowed by user already and invoke postNewBookListToUser() to send data to db
    void postNewBookListToUser();
    //for borrowing
    bool isBookAvailable_=false;
    QJsonArray userBookList_={};
public slots:
    void on_pushButton_borrowBook_clicked();
};

#endif // BOOKDETAILS_H
