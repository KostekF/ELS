#include "Bookdetails.h"
#include "ui_Bookdetails.h"

BookDetails::BookDetails(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookDetails)
{
    ui->setupUi(this);
}

BookDetails::~BookDetails()
{
    delete ui;
}
