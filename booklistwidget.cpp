#include "booklistwidget.h"
#include "ui_booklistwidget.h"

bookListWidget::bookListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bookListWidget)
{
    ui->setupUi(this);
}

bookListWidget::~bookListWidget()
{
    delete ui;
}

void bookListWidget::setMainTitle(QString author, QString title)
{
    QString combined=author+" / "+title;
    ui->label_mainTitle->setText(combined);
}

void bookListWidget::setLabelPhoto(QString resAddress)
{
    //TODO: add this function if photos will appear in database
    //ui->label_photo
}

void bookListWidget::setDescription(QString description)
{
     ui->label_description->setWordWrap(true);
    ui->label_description->setText(description);
}

void bookListWidget::setKeywords(QString keywords)
{
    ui->label_key_words->setText(keywords);
}


