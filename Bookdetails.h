#ifndef BOOKDETAILS_H
#define BOOKDETAILS_H

#include <QDialog>
#include"Book.h"
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
    Book book;
public slots:
    void on_pushButton_borrowBook_clicked();
};

#endif // BOOKDETAILS_H
