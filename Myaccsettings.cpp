#include "Myaccsettings.h"
#include "ui_Myaccsettings.h"
#include"QDebug"

//TODO: add something else to this class? (buttons, labels, etc)

MyAccSettings::MyAccSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyAccSettings)
{
    ui->setupUi(this);

    //Set focus to "My books" tab
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





}

MyAccSettings::~MyAccSettings()
{
    delete ui;
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
