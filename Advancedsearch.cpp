#include "Advancedsearch.h"
#include "ui_Advancedsearch.h"
#include <QStringList>
#include"QDebug"
Advancedsearch::Advancedsearch(QWidget *parent) :
    QDialog(parent),categoriesCounter_(1),
    ui(new Ui::Advancedsearch)
{
    ui->setupUi(this);

    AdvSearchOneLineWidget *firstLine=new AdvSearchOneLineWidget(true);
    ui->verticalLayout_lineWidgets->addWidget(firstLine);


    connect(firstLine,SIGNAL(plusClicked()),this,SLOT(on_widget_plus_clicked()));


    //Add checkBoxes to QListWidget
    QListWidgetItem* item = new QListWidgetItem("Kategoria 1", ui->listWidget_categories);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
    item->setCheckState(Qt::Unchecked); // AND initialize check state

    item = new QListWidgetItem("Kategoria 2", ui->listWidget_categories);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
    item->setCheckState(Qt::Unchecked); // AND initialize check state

    item = new QListWidgetItem("Kategoria 3", ui->listWidget_categories);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
    item->setCheckState(Qt::Unchecked); // AND initialize check state

    item = new QListWidgetItem("Kategoria 4", ui->listWidget_categories);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
    item->setCheckState(Qt::Unchecked); // AND initialize check state



}

Advancedsearch::~Advancedsearch()
{
    delete ui;

}


void Advancedsearch::on_widget_plus_clicked()
{
    qDebug("plus clicked");
    if(categoriesCounter_<maxAdvLineWidgets_)
    {
    AdvSearchOneLineWidget *nextLine=new AdvSearchOneLineWidget();
    connect(nextLine,SIGNAL(plusClicked()),this,SLOT(on_widget_plus_clicked()));
    ui->verticalLayout_lineWidgets->addWidget(nextLine);
    categoriesCounter_++;
    qDebug()<<categoriesCounter_;
    }
}

void Advancedsearch::on_widget_minus_clicked()
{
//TODO:ADD deleting items
    //ui->verticalLayout_lineWidgets->
    qDebug("minus clicked");
}
