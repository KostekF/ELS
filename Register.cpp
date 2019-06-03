#include "Register.h"
#include "ui_Register.h"
#include <functional>
#include <QCryptographicHash>
#include<QDebug>
#include<QByteArray>
#include<QJsonObject>
#include<QJsonArray>
#include<QJsonDocument>
#include<QNetworkReply>
#include<QNetworkRequest>
#include<QMessageBox>
Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    networkManager=new QNetworkAccessManager();
    ui->lineEdit_login->setPlaceholderText("login");
    ui->lineEdit_pass->setPlaceholderText("hasło");
    ui->lineEdit_mail->setPlaceholderText("e-mail");
    ui->lineEdit_name->setPlaceholderText("imię");
    ui->lineEdit_lastname->setPlaceholderText("nazwisko");

    //Set logo img in login screen
    QPixmap pixmap(":/img/img/croppedlogo.png");
    ui->label_logoLogin->setAlignment(Qt::AlignCenter);
    ui->label_logoLogin->setPixmap(pixmap.scaled(ui->label_logoLogin->size(),Qt::KeepAspectRatio));

}

Register::~Register()
{
    delete ui;
    delete networkManager;
}

void Register::on_pushButton_clicked()
{
    //TODO register user!

    bool allLinesWritten=true;
    if(ui->lineEdit_name->text().isEmpty()) allLinesWritten=false;
    if(ui->lineEdit_lastname->text().isEmpty()) allLinesWritten=false;
    if(ui->lineEdit_mail->text().isEmpty()) allLinesWritten=false;
    if(ui->lineEdit_login->text().isEmpty()) allLinesWritten=false;
    if(ui->lineEdit_pass->text().isEmpty()) allLinesWritten=false;


    if(!allLinesWritten)
    {
      QMessageBox::information(this, "Błąd danych", "<font size = 10 color = red >Sprawdź czy wpisałeś wszystkie wymagane dane.</font>", QMessageBox::Ok);
    }
    else
    {

        //Check if there is user with given login in db
        QString myLogin = ui->lineEdit_login->text();

        QNetworkRequest request1(QUrl("http://localhost:8080/user/?login="+myLogin));
        QNetworkReply *reply1 = networkManager->get(request1);
        connect(reply1, &QNetworkReply::finished, this, [this, reply1] {
            reply1->deleteLater();
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(reply1->readAll());
            const QJsonArray usersArray = jsonDoc.array();
            qDebug()<<"connection succesful, parsing JSON";

            if(usersArray.isEmpty())
            {
                qDebug()<<"No users with given login";
                postRegisterUser();
                this->close();
            }
            else
            {
                qDebug()<<"ERROR: Found user with this login!!!";
                 QMessageBox::information(this, "Błąd danych", "<font size = 10 color = red >Podany login jest już zajęty.</font>", QMessageBox::Ok);

            }
        });





    }
}


//Register user in db
void Register::postRegisterUser()
{
    QString myPass =ui->lineEdit_pass->text();
    QByteArray b= myPass.toLocal8Bit();
    QString hash= QCryptographicHash::hash(b,QCryptographicHash::Sha256);
    qDebug()<<"Hash: "<<hash;

    QJsonObject obj{
        {"email", ui->lineEdit_mail->text()},
        { "loan", QJsonArray({})},
        { "login", ui->lineEdit_login->text()},
        { "name", ui->lineEdit_name->text()},
        { "password",hash},
        { "surname", ui->lineEdit_lastname->text()},
        { "userType", "READER"}
    };

    QNetworkRequest request(QUrl("http://localhost:8080/user/create"));
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

            QMessageBox::information(this, "Poprawna rejestracja", "<font size = 10 color = green >Zarejestrowano użytkownika! Zapraszamy do korzystania z biblioteki.</font>", QMessageBox::Ok);
        }
        else {
            QMessageBox::information(this, "Błąd rejestracji", "<font size = 10 color = red >Nie udało się zarejestrować, sprawdź wszystkie dane/połączenie!</font>", QMessageBox::Ok);
        }

    });
}
