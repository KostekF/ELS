#include "Advsearchonelinewidget.h"
#include "ui_Advsearchonelinewidget.h"

AdvSearchOneLineWidget::AdvSearchOneLineWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdvSearchOneLineWidget)
{
    ui->setupUi(this);

    //Create plus image
    QPixmap pixmap(":/img/img/plusSign.png");
    ui->widget_plus->setAlignment(Qt::AlignCenter);
    ui->widget_plus->setPixmap(pixmap.scaled(ui->widget_plus->size(),Qt::KeepAspectRatio));

    //create minus image
    pixmap.load(":/img/img/minusSign.png");
    ui->widget_minus->setAlignment(Qt::AlignCenter);
    ui->widget_minus->setPixmap(pixmap.scaled(ui->widget_minus->size(),Qt::KeepAspectRatio));

        //Add items to combobox
    QStringList listaKategorii={"Autor","Tytuł","Słowa kluczowe"};
    ui->comboBox->insertItems(0,listaKategorii);

}

AdvSearchOneLineWidget::AdvSearchOneLineWidget(bool minusHidden, QWidget *parent):
    QDialog(parent),ui(new Ui::AdvSearchOneLineWidget)
{
    ui->setupUi(this);

    //Create plus image
    QPixmap pixmap(":/img/img/plusSign.png");
    ui->widget_plus->setAlignment(Qt::AlignCenter);
    ui->widget_plus->setPixmap(pixmap.scaled(ui->widget_plus->size(),Qt::KeepAspectRatio));

    //create minus image
    if(minusHidden)
    {pixmap.load(":/img/img/whiteMinus.png");}
    else
    {pixmap.load(":/img/img/minusSign.png");}

    ui->widget_minus->setAlignment(Qt::AlignCenter);
    ui->widget_minus->setPixmap(pixmap.scaled(ui->widget_minus->size(),Qt::KeepAspectRatio));


    //Add items to combobox
    QStringList listaKategorii={"Autor","Tytuł","Słowa kluczowe"};
    ui->comboBox->insertItems(0,listaKategorii);

}

AdvSearchOneLineWidget::~AdvSearchOneLineWidget()
{
    delete ui;
}

void AdvSearchOneLineWidget::hideMinusSign()
{
    ui->widget_minus->setVisible(false);
}

void AdvSearchOneLineWidget::on_widget_plus_clicked()
{
    emit plusClicked();
}

void AdvSearchOneLineWidget::on_widget_minus_clicked()
{
    emit minusClicked();
}



