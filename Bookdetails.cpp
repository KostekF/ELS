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
        { "userId", g_userID},               //TODO change this global
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

    });
}

void BookDetails::updateBookAvailability()
{
    QJsonObject  obj
    {
      {"bookavailability", "UNAVAILABLE"}
    };

    QNetworkRequest request(QUrl("http://localhost:8080/book/update/"+book_.getBookID()));
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
        }

    });
}

void BookDetails::updateUserBooklist()
{

    //Get books (array) that user already borrowed from library
    QNetworkRequest requestBookAvail(QUrl("http://localhost:8080/user/"+g_userID)); //TODO: change this global
    QNetworkReply *reply = networkManager->get(requestBookAvail);
    connect(reply, &QNetworkReply::finished, this, [this, reply] {
        reply->deleteLater();
        qDebug()<<"updateUserBooklist() - connection succesful, parsing JSON";
        const QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        const QJsonObject user = jsonDoc.object();

        //update userBookList with new borrowed book
        userBookList_=user.value(QString("loan")).toArray();
        userBookList_.append(book_.getBookID());
        qDebug()<<"added book "<<book_.title()<<" to user book list.\nUserBookList:"<<userBookList_;
        postNewBookListToUser();
        //update db with new userbooklist

    }

    );
}

void BookDetails::postNewBookListToUser()
{
    QJsonObject obj {
      {"loan",userBookList_}
    };
    qDebug()<<"postNewBookListToUser "<<obj;
    QNetworkRequest request(QUrl("http://localhost:8080/user/update/"+g_userID));       //TODO: change this global var
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
              qDebug()<<"on_pushButton_borrowBook_clicked() - connection succesful, parsing JSON";
          const QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
          const QJsonObject book = jsonDoc.object();
          //qDebug()<<book;
           QString isBookAvailable=book.value(QString("bookavailability")).toString();
           if(isBookAvailable=="AVAILABLE")
           {

               qDebug()<<"Book available";

               updateBookAvailability();
               createLoan();
               updateUserBooklist();
           }
           else{
               qDebug()<<"Book unavailable";

           }

          }
      );
}
