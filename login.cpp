#include "login.h"
#include "ui_login.h"
#include"QFocusEvent"
#include"QDebug"
#include "mainwindow.h"
#include <QCryptographicHash>
#include<QByteArray>
#include<QJsonObject>
#include<QJsonArray>
#include<QJsonDocument>
#include<QNetworkReply>
#include<QNetworkRequest>
#include<QMessageBox>

extern QString g_userID;

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    networkManager=new QNetworkAccessManager();
    ui->lineEdit_login->setPlaceholderText("login");
    ui->lineEdit_pass->setPlaceholderText("hasło");


    QFont font( "Ubuntu", 8,QFont::Cursive);
    ui->widget_resetPass->setFont(font);
    ui->widget_resetPass->setText("Zapomniałeś hasła?");

    ui->widget_register->setFont(font);
    ui->widget_register->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->widget_register->setText("Zarejestruj się");



    //Set logo img in login screen
    QPixmap pixmap(":/img/img/croppedlogo.png");
    ui->label_logoLogin->setAlignment(Qt::AlignCenter);
    ui->label_logoLogin->setPixmap(pixmap.scaled(ui->label_logoLogin->size(),Qt::KeepAspectRatio));


}

login::~login()
{
    delete ui;
    delete networkManager;
}





void login::on_pushButton_login_clicked()
{
    bool allLinesWritten=true;
    if(ui->lineEdit_login->text().isEmpty()) allLinesWritten=false;
    if(ui->lineEdit_pass->text().isEmpty()) allLinesWritten=false;


    if(!allLinesWritten)
    {
        QMessageBox::information(this, "Błąd danych", "<font size = 10 color = red >Sprawdź czy wpisałeś wszystkie wymagane dane.</font>", QMessageBox::Ok);
    }
    else
    {

        checkLoginCredentials();

    }
}




void login::on_widget_register_clicked()
{
    regDialog = new Register(this);
    regDialog->setModal(true);
    regDialog->show();
    regDialog->setFixedSize(regDialog->size());
}

void login::on_widget_resetPass_clicked()
{
    resetDialog = new ResetPassword(this);
    resetDialog->setModal(true);
    resetDialog->show();
    resetDialog->setFixedSize(resetDialog->size());
}

void login::checkLoginCredentials()
{
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
            QMessageBox::warning(this, "Błąd logowania", "<font size = 10 color = red >Nie udało się zalogować, sprawdź wszystkie dane!</font>", QMessageBox::Ok);
        }
        else
        {
            qDebug()<<"Found user with this login!!!";
            QString myPass=ui->lineEdit_pass->text();
            QByteArray b= myPass.toLocal8Bit();
            QString hash= QCryptographicHash::hash(b,QCryptographicHash::Sha256);
            QJsonObject user =usersArray[0].toObject();
            QString dbHash=user["password"].toString();
            qDebug()<<"Hash:    "<<hash;
            qDebug()<<"db hash: "<<dbHash;

            if(hash==dbHash)
            {
                g_userID=user["id"].toString();
                qDebug()<<"id z obliczen: "<<user["id"].toString();
                qDebug()<<"id z globalnej: "<<g_userID;
                emit loginSuccessful();
                this->close();
            }
            else
            {
                QMessageBox::warning(this, "Błąd logowania", "<font size = 10 color = red >Nie udało się zalogować, sprawdź wszystkie dane!</font>", QMessageBox::Ok);
            }
        }
    });
}
