#include "librarywindowwidget.h"
#include "ui_librarywindowwidget.h"
#include"QDebug"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include"QFile"
libraryWindowWidget::libraryWindowWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::libraryWindowWidget)
{
    ui->setupUi(this);
    ui->lineEdit_wyszukaj->setPlaceholderText("wpisz tytuł, autora lub słowa kluczowe");

    //create separating line
    line=new QFrame;
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    ui->verticalLayout_up->addWidget(line);

    //test?
    readJson();
}

libraryWindowWidget::~libraryWindowWidget()
{
    delete ui;

}





void libraryWindowWidget::readJson(QString json)
{


          //read json from resource file or from argument of function
          QString val;
          QFile file;
          if(json=="")
          {
              file.setFileName(":/json/json_example/example.json");
              file.open(QIODevice::ReadOnly | QIODevice::Text);
              val = file.readAll();
              file.close();
          }
          else
              val=json;




          //parse books json and assign to vector<Book> vBooks_
          QJsonDocument jsonDoc = QJsonDocument::fromJson(val.toUtf8());
          QJsonObject jsonObj = jsonDoc.object();
          QJsonValue value = jsonObj.value(QString("books"));
          //if correct json with books was given
          if(value.isArray())
          {
              QJsonArray booksArray=value.toArray();

              //iterate over every book in array and assign values to variables
              for(QJsonArray::const_iterator itr=booksArray.constBegin();itr!=booksArray.constEnd();++itr)
              {
                 QJsonObject book=itr->toObject();
                 QJsonObject author=book.value(QString("author")).toObject();

                 authorStruct authorStru;
                 authorStru.name=author.value(QString("name")).toString();
                 authorStru.last_name=author.value(QString("last_name")).toString();;

                 QString category=book.value(QString("category")).toString();
                 QString title=book.value(QString("title")).toString();
                 QString description=book.value(QString("description")).toString();
                 QString key_words=book.value(QString("key_words")).toString();
                 QString release_date=book.value(QString("release_date")).toString();
                 QJsonArray jsArr= book.value(QString("book_ids")).toArray();

                 std::vector<QString> book_ids;
                 //iterate over book_ids
                 for(QJsonArray::const_iterator itr=jsArr.constBegin();itr!=jsArr.constEnd();++itr)
                 {

                    book_ids.push_back(itr->toString());
                 }


                //assign above variables to Book and push Book to vector<Book>
                Book exBook(authorStru,category,title, description, key_words, release_date,book_ids);
                vBooks_.push_back(exBook);

              }

            //  qDebug()<<vBooks_[0].category();

          }//if(value.isArray())

          //TODO: 3) Assign every value to some label?





}
