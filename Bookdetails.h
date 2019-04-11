#ifndef BOOKDETAILS_H
#define BOOKDETAILS_H

#include <QDialog>

namespace Ui {
class BookDetails;
}

class BookDetails : public QDialog
{
    Q_OBJECT

public:
    explicit BookDetails(QWidget *parent = 0);
    ~BookDetails();

private:
    Ui::BookDetails *ui;
};

#endif // BOOKDETAILS_H
