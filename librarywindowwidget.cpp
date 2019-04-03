#include "librarywindowwidget.h"
#include "ui_librarywindowwidget.h"

libraryWindowWidget::libraryWindowWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::libraryWindowWidget)
{
    ui->setupUi(this);
}

libraryWindowWidget::~libraryWindowWidget()
{
    delete ui;
}
