#include "Bookdetails.h"
#include "ui_Bookdetails.h"

BookDetails::BookDetails(Book book,QWidget *parent) :
    QDialog(parent),book(book),
    ui(new Ui::BookDetails)
{
    ui->setupUi(this);
    ui->label_category->setText(book.category());
    ui->label_description->setWordWrap(true);
    ui->label_description->setText(book.description());

    ui->label_keywords->setText(book.key_words());
    ui->label_mainTitle->setText(book.author().last_name +" "+ book.author().name  + " / "+book.title());
    ui->label_releaseDate->setText(book.release_date());

    for(int i=0; i<book.book_ids().size();++i)
    {
        QLabel * label=new QLabel(this);
        label->setText(book.book_ids()[i]);
        ui->verticalLayout_ID->addWidget(label);

        QLabel * label2=new QLabel(this);
        label2->setText("TEST WOLNE");
        ui->verticalLayout_Status->addWidget(label2);

        QLabel * label3=new QLabel(this);
        label3->setText("TEST");
        ui->verticalLayout_returnDate->addWidget(label3);
    }



}

BookDetails::~BookDetails()
{
    delete ui;
}

void BookDetails::on_pushButton_borrowBook_clicked()
{

    //TODO: check if book is available and then borrow book
}
