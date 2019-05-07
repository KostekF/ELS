#include "Advancedsearch.h"
#include "ui_Advancedsearch.h"
#include <QStringList>
#include"QDebug"
#include"QSignalMapper"

Advancedsearch::Advancedsearch(QWidget *parent) :
    QDialog(parent),categoriesCounter_(1),
    ui(new Ui::Advancedsearch)
{
    ui->setupUi(this);

    //Create first line with advanced searching (no minus sign included)
    firstLine=new AdvSearchOneLineWidget(true);
    ui->verticalLayout_lineWidgets->addWidget(firstLine);

    //Connect signal (plus clicked) from advanced searching line to slot from this class
    connect(firstLine,SIGNAL(plusClicked()),this,SLOT(on_widget_plus_clicked()));



    //Add checkBoxes with categories to choose to QListWidget
    QListWidgetItem* item = new QListWidgetItem("Dowolna kategoria", ui->listWidget_categories);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
    item->setCheckState(Qt::Checked); // AND initialize check state

    item = new QListWidgetItem("Kategoria 1", ui->listWidget_categories);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
    item->setCheckState(Qt::Unchecked); // AND initialize check state

    item = new QListWidgetItem("Kategoria 2", ui->listWidget_categories);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
    item->setCheckState(Qt::Unchecked); // AND initialize check state

    item = new QListWidgetItem("Kategoria 3", ui->listWidget_categories);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
    item->setCheckState(Qt::Unchecked); // AND initialize check state


    connect(ui->listWidget_categories,SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(on_listWidget_categories_itemClicked(QListWidgetItem*)));

}

Advancedsearch::~Advancedsearch()
{
    delete ui;

}


void Advancedsearch::on_widget_plus_clicked()
{
   // qDebug("plus clicked");

    //Create up to as many categories as there are existing in database
    if(categoriesCounter_<maxAdvLineWidgets_)
    {
        //Create line with category and input and + and - buttons
        AdvSearchOneLineWidget *nextLine=new AdvSearchOneLineWidget();

        //Connect plus clicked and minus clicked signals with slots
        connect(nextLine,SIGNAL(plusClicked()),this,SLOT(on_widget_plus_clicked()));

        //Add QsignalMapper to pass int argument to slot on_widget_minus_clicked
        //This int argument shows us which row in QListWidget was clicked
        //Those 4 below lines are bassicaly (1) connect below
        // (1) connect(nextLine,SIGNAL(minusClicked()),this,SLOT(on_widget_minus_clicked(ui->verticalLayout_lineWidgets->count()));
        QSignalMapper* signalMapper = new QSignalMapper (this) ;
        connect(nextLine,SIGNAL(minusClicked()),signalMapper,SLOT(map()));
        signalMapper -> setMapping (nextLine, nextLine);
        connect (signalMapper, SIGNAL(mapped(QWidget *)), this, SLOT(on_widget_minus_clicked(QWidget *))) ;


        //Add item to layout
        ui->verticalLayout_lineWidgets->addWidget(nextLine);
        //increment number of categories line widgets existing
        categoriesCounter_++;

      //  qDebug()<<categoriesCounter_;
      //  qDebug()<<"Count on plus = "<<ui->verticalLayout_lineWidgets->count();
    }
}

//Delete item from Layout when minus is clicked
void Advancedsearch::on_widget_minus_clicked(QWidget * widget)
{    
    widget->setVisible(false);
    ui->verticalLayout_lineWidgets->removeWidget(widget);
    delete widget;
    //decrement number of categories line widgets existing
    categoriesCounter_--;
   // qDebug()<<"Count on minus = "<<ui->verticalLayout_lineWidgets->count();
}


void Advancedsearch::on_listWidget_categories_itemClicked(QListWidgetItem* item)
{
    //qDebug()<<"item from listWidget_categories changed";
    // qDebug()<<item->checkState();
}

void Advancedsearch::on_pushButton_wyszukaj_clicked()
{
    //TODO: Add sending data to server
    qDebug()<<"sending data to server";
}
