#include "intro.h"
#include "ui_intro.h"
#include"QFile"
#include "QPixmap"
#include"QDebug"
#include"login.h"
#include"mainwindow.h"
intro::intro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::intro)
{
    ui->setupUi(this);

    QFile styleFile(":/stylesheets/stylesheets/qpushbutton.qss");
    styleFile.open(QFile::ReadOnly);
    QPushButton:setStyleSheet(QString::fromLatin1(styleFile.readAll()));
    styleFile.close();




    QPixmap pixmap(":/img/img/logo.png");
    int height=ui->label_logoPhoto->height();
    int width=ui->label_logoPhoto->width();
    qDebug()<<width<<", "<<height<<"\n";
     ui->label_logoPhoto->setAlignment(Qt::AlignCenter);

    ui->label_logoPhoto->setPixmap(pixmap.scaled(ui->label_logoPhoto->size(),Qt::KeepAspectRatio));
}

intro::~intro()
{
    delete ui;
}

void intro::on_pushButton_clicked()
{
    login * logDialog = new login(this);

    connect(logDialog,SIGNAL(loginSuccessful()),parent(),SLOT(showLibWindow()));
    logDialog->setModal(true);
    logDialog->show();
    logDialog->setFixedSize(logDialog->size());
}
