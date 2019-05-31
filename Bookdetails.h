#ifndef BOOKDETAILS_H
#define BOOKDETAILS_H

#include <QDialog>
#include"Book.h"
#include<QNetworkAccessManager>

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
    //for borrowing
    bool isBookAvailable_=false;
public slots:
    void on_pushButton_borrowBook_clicked();
};

#endif // BOOKDETAILS_H
