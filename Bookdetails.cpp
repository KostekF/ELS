#include "Bookdetails.h"
#include "ui_Bookdetails.h"

#include"QDebug"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include<QNetworkReply>
#include<QMessageBox>
//TODO: delete this
extern QString g_userID;


BookDetails::BookDetails(Book book,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookDetails)
{
    ui->setupUi(this);
    book_=book;
    networkManager=new QNetworkAccessManager();
    ui->label_category->setText(book.category());
    ui->label_description->setWordWrap(true);
    ui->label_description->setText(book.description());

    ui->label_keywords->setText(book.key_words());
    ui->label_mainTitle->setText(book.author().last_name +" "+ book.author().name  + " / "+book.title());
    ui->label_releaseDate->setText(book.release_date());
    ui->label_bookID->setText(book.getBookID());
    ui->label_bookID->setTextInteractionFlags(Qt::TextSelectableByMouse);

    if(book.getBookAvail()=="AVAILABLE")
    {
        ui->label_bookStatus->setText("Dostępna");
    }
    else {
        ui->label_bookStatus->setText("Wypożyczona");
    }

    /*
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
    */



}

BookDetails::~BookDetails()
{
    delete ui;
}

void BookDetails::createLoan()
{
    QString beginDate = QDate::currentDate().toString("yyyy-MM-dd");
    //  qDebug()<<"CUrr date: "<<beginDate;
    QString finishDate=QDate::currentDate().addMonths(2).toString("yyyy-MM-dd");
    //  qDebug()<<"Finish date: "<<finishDate;

    QJsonObject  obj
    {
        { "bookId",book_.getBookID()},
        { "userId", g_userID},
        { "loanStatus", "AVAILABLE"},
        { "beginDate", beginDate},
        { "finishDate", finishDate}
    };


    QNetworkRequest request(QUrl("http://localhost:8080/loan/create"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = networkManager->post(request,QJsonDocument(obj).toJson());



    connect(reply, &QNetworkReply::finished, this, [this, reply] {
        reply->deleteLater();
        QVariant statusCode = reply->attribute( QNetworkRequest::HttpStatusCodeAttribute );
        int status = statusCode.toInt();

        if ( status == 201 )
        {
            QString reason = reply->attribute( QNetworkRequest::HttpReasonPhraseAttribute ).toString();
            qDebug() << reason;

            QMessageBox::information(this, "Wypożyczyłeś książkę!", "<font size = 10 color = green >Wypożyczono książkę ze zbioru. Zapraszamy po odbiór do biblioteki!</font>", QMessageBox::Ok);
        }
        else {
            QMessageBox::information(this, "Błąd wypożyczenia", "<font size = 10 color = red >Nie udało się wypożyczyć książki</font>", QMessageBox::Ok);
        }
        const QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        const QJsonObject obj = doc.object();
        qDebug()<<obj;
        if (obj.value("status").toString() == "OK") {
            qDebug()<<"Status OK";
        } else {
            qWarning() << "ERROR" << obj.value("error").toString();
        }
    });
}



void BookDetails::on_pushButton_borrowBook_clicked()
{

     //check if book is available

      QNetworkRequest requestBookAvail(QUrl("http://localhost:8080/book/"+book_.getBookID()));
      QNetworkReply *reply = networkManager->get(requestBookAvail);
      connect(reply, &QNetworkReply::finished, this, [this, reply] {
          reply->deleteLater();
              qDebug()<<"connection succesful, parsing JSON";
          const QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
          const QJsonObject book = jsonDoc.object();
          //qDebug()<<book;
           QString isBookAvailable=book.value(QString("bookavailability")).toString();
           if(isBookAvailable=="AVAILABLE")
           {

               qDebug()<<"Book available";

               //        //TODO: update book availability


               createLoan();


              //TODO: update user bookList
           }
           else{
               qDebug()<<"Book unavailable";

           }

          }
      );


//    if(isBookAvailable_)
//    {
//        //TODO: update book availability

//        //TODO: create Loan

//


//        //TODO: update user bookList




   // QNetworkRequest request(QUrl("http://localhost:8080/book/"+ui->label_bookID->text()));
   // reply = networkManager->get(requestBookAvail);

}
