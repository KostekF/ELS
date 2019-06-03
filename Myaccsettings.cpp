#include "Myaccsettings.h"
#include "ui_Myaccsettings.h"
#include"QDebug"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include<QNetworkReply>
#include<QMessageBox>
//TODO: add something else to this class? (buttons, labels, etc)

extern QString g_userID;

MyAccSettings::MyAccSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyAccSettings)
{

    ui->setupUi(this);
    networkManager = new QNetworkAccessManager();

    //Set focus  to "My books" tab
    ui->tabWidget_options->setCurrentIndex(0);

    ui->label_passErrorMsg->setVisible(false);
    ui->label_passErrorMsg->setWordWrap(true);
    //Change type of lineEdit so passes will not be visible
    ui->lineEdit_oldPass->setEchoMode(QLineEdit::Password);
    ui->lineEdit_newPass1->setEchoMode(QLineEdit::Password);
    ui->lineEdit_newPass2->setEchoMode(QLineEdit::Password);

    //resize columns into halves
    ui->tableWidget_books->setColumnWidth(0, this->width()/2);
    ui->tableWidget_books->horizontalHeader()->setStretchLastSection(true);




    /*
        //Just for tests add some data to my books
    ui->tableWidget_books->insertRow(ui->tableWidget_books->rowCount());
    //Add data to created row
    ui->tableWidget_books->setItem(ui->tableWidget_books->rowCount()-1, 0,new QTableWidgetItem("Stephen King / Misery"));
    ui->tableWidget_books->item(ui->tableWidget_books->rowCount()-1, 0)->setTextAlignment(Qt::AlignCenter);

    ui->tableWidget_books->setItem   ( ui->tableWidget_books->rowCount()-1, 1, new QTableWidgetItem("06.08.2019"));
    ui->tableWidget_books->item(ui->tableWidget_books->rowCount()-1, 1)->setTextAlignment(Qt::AlignCenter);


    //add second book
    ui->tableWidget_books->insertRow(ui->tableWidget_books->rowCount());

    //Add data to created row
    ui->tableWidget_books->setItem(ui->tableWidget_books->rowCount()-1, 0,new QTableWidgetItem("George R. R. Martin / Taniec ze smokami"));
    ui->tableWidget_books->item(ui->tableWidget_books->rowCount()-1, 0)->setTextAlignment(Qt::AlignCenter);

    ui->tableWidget_books->setItem   ( ui->tableWidget_books->rowCount()-1, 1, new QTableWidgetItem("16.09.2019"));
    ui->tableWidget_books->item(ui->tableWidget_books->rowCount()-1, 1)->setTextAlignment(Qt::AlignCenter);
*/
    ui->lineEdit_add_bookDate->setPlaceholderText("Data format ex.: 2017-08-30");
    ui->lineEdit_add_bookKeywords->setPlaceholderText("słowo1, słowo2, ...");
    ui->lineEdit_edit_bookDate->setPlaceholderText("Data format ex.: 2017-08-30");
     ui->lineEdit_edit_bookKeywords->setPlaceholderText("słowo1, słowo2, ...");




showUsersBooks();

}

MyAccSettings::~MyAccSettings()
{
    delete ui;
    delete networkManager;
}



void MyAccSettings::on_pushButton_clicked()
{
    bool goodPasses = true;
    QString newPass = ui->lineEdit_newPass1->text();
    QString newPass2 = ui->lineEdit_newPass2->text();

    //Compare if two passes match
    if(newPass != newPass2)
    {
        qDebug()<<"New and repeated pass are not the same";
        ui->label_passErrorMsg->setVisible(true);
        ui->label_passErrorMsg->setStyleSheet("QLabel {color : red; }");
        ui->label_passErrorMsg->setText("ERROR: New and repeated password are not the same");
        goodPasses = false;

    }

    //Check if new pass has correct length
    if(newPass.length()<8 && goodPasses)
    {
        qDebug()<<"New pass too short, it should be minimum 8 characters long"; //TODO: should it be min 8 characters?
        ui->label_passErrorMsg->setVisible(true);
        ui->label_passErrorMsg->setStyleSheet("QLabel {color : red; }");
        ui->label_passErrorMsg->setText("ERROR: New pass too short, it should be minimum 8 characters long");
        goodPasses = false;
    }

    //TODO: check if old pass is correct (compare hashes of old pass and database pass)
    /*
    if(old pass_hash != dbHash)
    {
        qDebug()<<"Old pass is not correct";
        goodPasses = false;
    }
    */

    //TODO: add additional new pass restrictions?

    //If everything is okay connect with server
    if(goodPasses)
    {
        qDebug()<<"passwords are the same, changing password to new password, beep, boop";
        ui->label_passErrorMsg->setVisible(true);
        ui->label_passErrorMsg->setStyleSheet("QLabel {color : green; }");
        ui->label_passErrorMsg->setText("Passwords correct, check your e-mail?");
        //TODO: if everything is okay change hash in database to new pass' hash
    }




}

void MyAccSettings::on_pushButton_delBook_clicked()
{
    //TODO: check if book was deleted succesfully and maybe show some window which book was it?
    if(ui->lineEdit_del_ID->text().length()>0)
    {
        QNetworkRequest request(QUrl("http://localhost:8080/book/"+ui->lineEdit_del_ID->text()));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


        QMessageBox::StandardButton reply;

        reply = QMessageBox::question(this, "Usuwanie książki ze zbioru", "<font size = 10 color = red >Czy na pewno chcesz usunąć książkę o ID </font> <font size = 10 color = blue >"+ ui->lineEdit_del_ID->text()+"</font><font size = 10 color = red > ze zbioru?</font>",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            networkManager->deleteResource(request);
            qDebug()<<"Deleting book with ID "<<ui->lineEdit_del_ID->text();
        } else {
            qDebug() << "Librarian decided to keep book in library";
        }
    }
    else
    {
        QMessageBox::warning(this, "Ostrzeżenie", "<font size = 10 color = red >Nie podałeś ID książki!</font>", QMessageBox::Ok);

    }

}

void MyAccSettings::on_pushButton_addBook_clicked()
{
    //color when user inputs wrong input

    QPalette palette;
    palette.setColor(QPalette::Base,Qt::red);
    palette.setColor(QPalette::Text,Qt::white);


    bool isAllOk=true;

    if(ui->lineEdit_add_authorName->text().isEmpty())
    {
       isAllOk=false;
       ui->lineEdit_add_authorName->setPalette(palette);
    }
    else{
     ui->lineEdit_add_authorName->setPalette(this->style()->standardPalette());
    }

    if(ui->lineEdit_add_authorSurname->text().isEmpty())
    {
       isAllOk=false;
       ui->lineEdit_add_authorSurname->setPalette(palette);
    }
    else{
     ui->lineEdit_add_authorSurname->setPalette(this->style()->standardPalette());
    }

    if(ui->lineEdit_add_bookDescription->text().isEmpty())
    {
       isAllOk=false;
       ui->lineEdit_add_bookDescription->setPalette(palette);
    }
    else{
     ui->lineEdit_add_bookDescription->setPalette(this->style()->standardPalette());
    }

    if(ui->lineEdit_add_bookKeywords->text().isEmpty())
    {
       isAllOk=false;
       ui->lineEdit_add_bookKeywords->setPalette(palette);
    }
    else{
     ui->lineEdit_add_bookKeywords->setPalette(this->style()->standardPalette());
    }

    if(ui->lineEdit_add_bookName->text().isEmpty())
    {
       isAllOk=false;
       ui->lineEdit_add_bookName->setPalette(palette);
    }
    else{
     ui->lineEdit_add_bookName->setPalette(this->style()->standardPalette());
    }


    QRegExp re("^(\\d\\d\\d\\d)-(\\d\\d)-(\\d\\d)$");  // a digit (\d), zero or more times (*)

    if(ui->lineEdit_add_bookDate->text().isEmpty() || !re.exactMatch(ui->lineEdit_add_bookDate->text()))
    {
       isAllOk=false;
       ui->lineEdit_add_bookDate->setPalette(palette);
    }
    else{
     ui->lineEdit_add_bookDate->setPalette(this->style()->standardPalette());
    }



    if(isAllOk)
    {
        QJsonObject  obj
        {
            {"author",QJsonObject{
                    {"name",ui->lineEdit_add_authorName->text()},
                    {"surname",ui->lineEdit_add_authorSurname->text()}
                }
            },
            {"bookcategory", "FANTASY"}, //TODO dodaj listę kategorii?
            {"description",ui->lineEdit_add_bookDescription->text()},
            {"keyWords",ui->lineEdit_add_bookKeywords->text()},
            {"name",ui->lineEdit_add_bookName->text()},
            {"releaseDate",ui->lineEdit_add_bookDate->text()},
            {"bookavailability","AVAILABLE"}

        };
        QNetworkRequest request(QUrl("http://localhost:8080/book/create"));
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

                QMessageBox::information(this, "Poprawne dodanie książki", "<font size = 10 color = green >Dodano książkę do zbioru!</font>", QMessageBox::Ok);
            }
            else {
                QMessageBox::information(this, "Błąd dodawania książki", "<font size = 10 color = red >Nie udało się dodać książki, sprawdź wszystkie dane/połączenie!</font>", QMessageBox::Ok);
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
}


void MyAccSettings::on_pushButton_editBook_clicked()
{
     //TODO: Edit book code when api is finished
    /*
    QJsonObject  obj
    {
        {"author","Alan Raczek"},
        {"name","Historia muzykow"}
    };
    QNetworkRequest request(QUrl("http://localhost:8080/book/update/" + TODOTODO ID ));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = networkManager->post(request,QJsonDocument(obj).toJson());
*/
    //color when user inputs wrong input

    QPalette palette;
    palette.setColor(QPalette::Base,Qt::red);
    palette.setColor(QPalette::Text,Qt::white);


    bool isAllOk=true;

    if(ui->lineEdit_edit_authorName->text().isEmpty())
    {
       isAllOk=false;
       ui->lineEdit_edit_authorName->setPalette(palette);
    }
    else{
     ui->lineEdit_edit_authorName->setPalette(this->style()->standardPalette());
    }

    if(ui->lineEdit_edit_authorSurname->text().isEmpty())
    {
       isAllOk=false;
       ui->lineEdit_edit_authorSurname->setPalette(palette);
    }
    else{
     ui->lineEdit_edit_authorSurname->setPalette(this->style()->standardPalette());
    }

    if(ui->lineEdit_edit_bookDescription->text().isEmpty())
    {
       isAllOk=false;
       ui->lineEdit_edit_bookDescription->setPalette(palette);
    }
    else{
     ui->lineEdit_edit_bookDescription->setPalette(this->style()->standardPalette());
    }

    if(ui->lineEdit_edit_bookKeywords->text().isEmpty())
    {
       isAllOk=false;
       ui->lineEdit_edit_bookKeywords->setPalette(palette);
    }
    else{
     ui->lineEdit_edit_bookKeywords->setPalette(this->style()->standardPalette());
    }

    if(ui->lineEdit_edit_bookName->text().isEmpty())
    {
       isAllOk=false;
       ui->lineEdit_edit_bookName->setPalette(palette);
    }
    else{
     ui->lineEdit_edit_bookName->setPalette(this->style()->standardPalette());
    }


    QRegExp re("^(\\d\\d\\d\\d)-(\\d\\d)-(\\d\\d)$");  // a digit (\d), zero or more times (*)

    if(ui->lineEdit_edit_bookDate->text().isEmpty() || !re.exactMatch(ui->lineEdit_edit_bookDate->text()))
    {
       isAllOk=false;
       ui->lineEdit_edit_bookDate->setPalette(palette);
    }
    else{
     ui->lineEdit_edit_bookDate->setPalette(this->style()->standardPalette());
    }
   QRegExp re1("^[a-zA-Z0-9_]{24}$");  // a digit (\d), zero or more times (*)

    if(ui->line_edit_bookID->text().isEmpty() || !re1.exactMatch(ui->line_edit_bookID->text()))
    {
       isAllOk=false;
       ui->line_edit_bookID->setPalette(palette);
    }
    else{
     ui->line_edit_bookID->setPalette(this->style()->standardPalette());
    }



    if(isAllOk)
    {
        qDebug()<<"Edit: all is ok";
        QJsonObject  obj
        {
            {"author",QJsonObject{
                    {"name",ui->lineEdit_edit_authorName->text()},
                    {"surname",ui->lineEdit_edit_authorSurname->text()}
                }
            },
            {"bookcategory", "FANTASY"}, //TODO dodaj listę kategorii?
            {"description",ui->lineEdit_edit_bookDescription->text()},
            {"keyWords",ui->lineEdit_edit_bookKeywords->text()},
            {"name",ui->lineEdit_edit_bookName->text()},
            {"releaseDate",ui->lineEdit_edit_bookDate->text()}

        };
        QNetworkRequest request(QUrl("http://localhost:8080/book/update/"+ui->line_edit_bookID->text()));
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

                QMessageBox::information(this, "Poprawne edytowanie książki", "<font size = 10 color = green >Edytowano książkę w zbiorze!</font>", QMessageBox::Ok);
            }
            else {
                QMessageBox::information(this, "Błąd edytowania książki", "<font size = 10 color = red >Nie udało się edytować książki, sprawdź wszystkie dane/połączenie!</font>", QMessageBox::Ok);
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
}


void MyAccSettings::on_pushButton_changeLoanDate_clicked()
{



    //Iterate over every loan to find loan ID of book given by librarian
    //Alternative: server gives method to return loan by bookID instead
    // of loanID
    QNetworkRequest request1(QUrl("http://localhost:8080/loan"));
    QNetworkReply *reply1 = networkManager->get(request1);
    connect(reply1, &QNetworkReply::finished, this, [this, reply1] {
        reply1->deleteLater();
        const QJsonDocument jsonDoc = QJsonDocument::fromJson(reply1->readAll());
        const QJsonArray loanArray = jsonDoc.array();
        qDebug()<<"connection succesful, parsing JSON";
         QString bookID="";
        //iterate over every loan in array and assign values to variables
        for(QJsonArray::const_iterator itr=loanArray.constBegin();itr!=loanArray.constEnd();++itr)
        {
            QJsonObject loan=itr->toObject();
            qDebug()<<loan;

            //TODO: Uncomment when Bartek adds removed to loan
           // QString bookIsAvail= loan.value(QString("loanStatus")).toString();

            //Skip removed loans
            //if(removed==true) {continue;}


            bookID=loan["bookId"].toString();
            if(bookID==ui->lineEdit_userExtend_bookID->text())
            {
                loanID_=loan["id"].toString();
                qDebug()<<"loan id: "<<loanID_;
                changeLoanFinishDate();
                break;
            }

        }
    });





}

void MyAccSettings::changeLoanFinishDate()
{
    QString finishDate=QDate::currentDate().addMonths(1).toString("yyyy-MM-dd");
    QJsonObject  obj
    {
        {"finishDate",finishDate},
        {"loanStatus","AVAILABLE"}
    };
    QNetworkRequest request(QUrl("http://localhost:8080/loan/update/"+loanID_));
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
            QString finishDate=QDate::currentDate().addMonths(1).toString("yyyy-MM-dd");
            QMessageBox::information(this, "Poprawne przedłużenie terminu książki", "<font size = 10 color = green >Przedłużono termin oddania książki do " +finishDate+ "!</font>", QMessageBox::Ok);
        }
        else {
            QMessageBox::information(this, "Błąd przedłużania książki", "<font size = 10 color = red >Nie udało się przedłużyć terminu książki, sprawdź wszystkie dane/połączenie!</font>", QMessageBox::Ok);
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

void MyAccSettings::showUsersBooks()
{
    //Get books (array) that user already borrowed from library
    QNetworkRequest requestBookAvail(QUrl("http://localhost:8080/user/"+g_userID)); //TODO: change this global
    QNetworkReply *reply = networkManager->get(requestBookAvail);
    connect(reply, &QNetworkReply::finished, this, [this, reply] {
        reply->deleteLater();
        qDebug()<<"showUsersBooks() get userbooks - connection succesful, parsing JSON";
        const QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        const QJsonObject user = jsonDoc.object();

        userBookList_=user.value(QString("loan")).toArray();


        for(QJsonArray::iterator itr=userBookList_.begin(); itr!= userBookList_.end();++itr)
        {
            QNetworkRequest getBook(QUrl("http://localhost:8080/book/"+(*itr).toString()));
            QNetworkReply *reply = networkManager->get(getBook);

            book_.setBookID((*itr).toString());

            //Get book info
            connect(reply, &QNetworkReply::finished, this, [this, reply] {
                reply->deleteLater();
                // qDebug()<<"showUsersBooks() get book info - connection succesful, parsing JSON";
                const QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
                const QJsonObject book = jsonDoc.object();
                QJsonObject author=book.value(QString("author")).toObject();

                authorStruct authorStru;
                authorStru.name=author.value(QString("name")).toString();
                authorStru.last_name=author.value(QString("surname")).toString();;


                //qDebug()<<book;

                book_.setTitle(book.value(QString("name")).toString());
                book_.setAuthor(authorStru);
                vBooks_.push_back(book_);


                //get date of giving book back to library

            }


            );

            QTime dieTime= QTime::currentTime().addMSecs(25);
               while (QTime::currentTime() < dieTime)
                   QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }




        for(int i=0;i<vBooks_.size();++i)
        {
            ui->tableWidget_books->insertRow(ui->tableWidget_books->rowCount());
            QNetworkRequest getLoan(QUrl("http://localhost:8080/loan/?bookId="+vBooks_[i].getBookID()));
            qDebug()<<"Book id: "<<vBooks_[i].getBookID();
            QNetworkReply *reply = networkManager->get(getLoan);

            //Get loan date info
            connect(reply, &QNetworkReply::finished, this,   [this, reply] {
                reply->deleteLater();
                // qDebug()<<"showUsersBooks() get loan info - connection succesful, parsing JSON";
                const QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());


                const QJsonArray jsonArr = jsonDoc.array();
                qDebug()<<"Array size: "<<jsonArr.size();
                QJsonObject loan;
                for(int i=0; i<jsonArr.size();++i)
                {
                    loan = jsonArr[i].toObject();
                   QString status= loan["loanStatus"].toString();
                   if(status=="AVAILABLE")
                   {
                       finishDate_=loan["finishDate"].toString().mid(0,10);

                       break;
                   }
                }


                qDebug()<<"DATE: "<<finishDate_;
                vfinishDates_.push_back(finishDate_);

            }
            );

            QTime dieTime= QTime::currentTime().addMSecs(100);
               while (QTime::currentTime() < dieTime)
                   QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            ui->tableWidget_books->setItem(ui->tableWidget_books->rowCount()-1, 0,new QTableWidgetItem(vBooks_[i].author().last_name + " "+ vBooks_[i].author().name +" / "+  vBooks_[i].title()));
            ui->tableWidget_books->item(i, 0)->setTextAlignment(Qt::AlignCenter);


            ui->tableWidget_books->setItem   (i, 1, new QTableWidgetItem(vfinishDates_[i]));
            ui->tableWidget_books->item(i, 1)->setTextAlignment(Qt::AlignCenter);

            //Set bigger font of cells in tableWidget
            QFont fnt;
            fnt.setPointSize(16);
            fnt.setFamily("MS Shell Dlg 2");
            const int rowCount = ui->tableWidget_books->rowCount();
            const int columnCount = ui->tableWidget_books->columnCount();
            QTableWidgetItem* selectedItem = ui->tableWidget_books->item(i, 0);
            selectedItem->setFont(fnt);
            QTableWidgetItem* selectedItem2 = ui->tableWidget_books->item(i, 1);
            selectedItem2->setFont(fnt);

        }




    }

    );

}

void MyAccSettings::updateBookAvailability()
{
    QJsonObject  obj
    {
        {"bookavailability", "AVAILABLE"}
    };

    QNetworkRequest request(QUrl("http://localhost:8080/book/update/"+ui->lineEdit_user_bookID->text()));
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

void MyAccSettings::updateLoanStatus()
{
    QString finishDate = QDate::currentDate().toString("yyyy-MM-dd");
    QJsonObject  obj
    {
        {"finishDate", finishDate},
        {"loanStatus","UNAVAILABLE"}
    };

    QNetworkRequest request(QUrl("http://localhost:8080/loan/update/"+loanID_));

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

void MyAccSettings::postDateAndStatus()
{

}

void MyAccSettings::delRemoveLoan()
{


            QNetworkRequest request(QUrl("http://localhost:8080/loan/"+loanID_));

            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            QNetworkReply *reply = networkManager-> deleteResource(request);



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

void MyAccSettings::postRemoveBookFromUserList()
{
    for(QJsonArray::iterator itr=userBookList_.begin(); itr!= userBookList_.end();++itr)
    {
        if((*itr)==ui->lineEdit_user_bookID->text())
        {
            itr=userBookList_.erase(itr);
            itr--;
        }
    }


    QJsonObject  obj
    {
        {"loan",userBookList_}
    };

    QNetworkRequest request(QUrl("http://localhost:8080/user/update/"+g_userID));   //TODO: change this global

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




void MyAccSettings::on_pushButton_returnBook_clicked()
{

    //GetLoanID
    QNetworkRequest request(QUrl("http://localhost:8080/loan/?bookId="+ui->lineEdit_user_bookID->text()));
    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply] {
        reply->deleteLater();
        qDebug()<<"updateUserBooklist() - connection succesful, parsing JSON";
        const QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());



        const QJsonArray jsonArr = jsonDoc.array();
        QJsonObject loan;
        for(int i=0; i<jsonArr.size();++i)
        {
            loan = jsonArr[i].toObject();
           QString status= loan["loanStatus"].toString();
           if(status=="AVAILABLE")
           {
               loanID_=loan["id"].toString();
               break;
           }
        }



        qDebug()<<"loanID: "<<loanID_;
        if(loanID_!="")
        {

            QMessageBox::StandardButton reply;

            reply = QMessageBox::question(this, "Oddawnie książki", "<font size = 10 color = red >Czy na pewno zwrócić książkę o ID =  </font> <font size = 10 color = blue >"+ ui->lineEdit_user_bookID->text()+"</font><font size = 10 color = red >?</font>",
                                          QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                qDebug()<<"Zwrócono książkę do zbioru "<<ui->lineEdit_del_ID->text();
                updateLoanStatus();
                delRemoveLoan();
                postRemoveBookFromUserList();
                updateBookAvailability();
            } else {
                qDebug() << "Zdecydowano się nie zwracać książki";
            }

        }

    }

    );


}
