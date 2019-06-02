#include "librarywindowwidget.h"
#include "ui_librarywindowwidget.h"


#include"QFile"
#include <QListWidget>
#include <QListWidgetItem>
#include"booklistwidget.h"
#include"Bookdetails.h"
#include<vector>
#include"QDebug"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include<QNetworkReply>
//http://localhost:8080/book





libraryWindowWidget::libraryWindowWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::libraryWindowWidget)
{
    ui->setupUi(this);
    ui->lineEdit_wyszukaj->setPlaceholderText("wpisz tytuł, autora lub słowa kluczowe");

    connect(ui->listWidget_booksList, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(itemInList_clicked(QListWidgetItem*)));

    m_nam = new QNetworkAccessManager();

    //test?
    //  readJson();//move this to search_clicked_btn slot?

    //ADD book widget to QListWidget
    /*
    int licznik=0;
    for(std::vector<Book>::iterator itr = vBooks_.begin();itr!=vBooks_.end();++itr)
        {
            //Creating a new list widget item whose parent is the listwidget itself
                QListWidgetItem *listWidgetItem = new QListWidgetItem(ui->listWidget_booksList);

                //Adding the item to the listwidget
                ui->listWidget_booksList->addItem (listWidgetItem);

                //Creating an object of the designed widget which is to be added to the listwidget
                bookListWidget *booklistwidget = new bookListWidget();
                //Assign data from database to booklist widget
                booklistwidget->setMainTitle(QString::number(licznik)+") "+itr->author().last_name +" "+ itr->author().name,itr->title());
                licznik++;
                booklistwidget->setKeywords(itr->key_words());
                booklistwidget->setDescription(itr->description());


                //Making sure that the listWidgetItem has the same size as the TheWidgetItem
                listWidgetItem->setSizeHint (booklistwidget->sizeHint ());

                //Finally adding the itemWidget to the list
                 ui->listWidget_booksList->setItemWidget (listWidgetItem, booklistwidget);

        }
*/


    /*
    QNetworkRequest request(QUrl("http://localhost:8080/book"));

    QNetworkReply *reply = m_nam->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply] {
        reply->deleteLater();
        const QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        const QJsonArray array = jsonDoc.array();

        for (const QJsonValue &value : array) {
            qDebug()<<(value["id"].toString());
            qDebug()<<(value["name"].toString());
            qDebug()<<(value["author"].toString());
        }
    });
*/
    on_pushButton_wyszukaj_clicked();

}

libraryWindowWidget::~libraryWindowWidget()
{
    delete ui;
    delete m_nam;

}




//just for offline tests
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
             QString bookID=book.value(QString("id")).toString();
            QString category=book.value(QString("category")).toString();
            QString title=book.value(QString("title")).toString();
            QString description=book.value(QString("description")).toString();
            QString key_words=book.value(QString("key_words")).toString();
            QString release_date=book.value(QString("release_date")).toString();
            QString bookAvail=book.value(QString("bookavailability")).toString();
            QJsonArray jsArr= book.value(QString("book_ids")).toArray();

            /*
                 std::vector<QString> book_ids;
                 //iterate over book_ids
                 for(QJsonArray::const_iterator itr=jsArr.constBegin();itr!=jsArr.constEnd();++itr)
                 {

                    book_ids.push_back(itr->toString());
                 }
                */

            //assign above variables to Book and push Book to vector<Book>
            Book exBook(authorStru,category,title, description, key_words, release_date,bookID,bookAvail);
            vBooks_.push_back(exBook);

        }

        //  qDebug()<<vBooks_[0].category();

    }//if(value.isArray())

    //TODO: 3) Assign every value to some label?





}



//Display books in QListWidget
void libraryWindowWidget::displayBooks()
{
    int licznik=0;
    qDebug()<<"Size of vBooks vector: "<<vBooks_.size();
    for(std::vector<Book>::iterator itr = vBooks_.begin();itr!=vBooks_.end();++itr)
    {
        //Creating a new list widget item whose parent is the listwidget itself
        QListWidgetItem *listWidgetItem = new QListWidgetItem(ui->listWidget_booksList);

        //Adding the item to the listwidget
        ui->listWidget_booksList->addItem (listWidgetItem);


        //Creating an object of the designed widget which is to be added to the listwidget
        bookListWidget *booklistwidget = new bookListWidget();


        //Assign data from database to booklist widget
        booklistwidget->setMainTitle(QString::number(licznik+1)+") "+itr->author().last_name +" "+ itr->author().name,itr->title());
        licznik++;
        booklistwidget->setKeywords(itr->key_words());
        booklistwidget->setDescription(itr->description());


        //Making sure that the listWidgetItem has the same size as the TheWidgetItem
        listWidgetItem->setSizeHint (booklistwidget->sizeHint ());

        //Finally adding the itemWidget to the list
        ui->listWidget_booksList->setItemWidget (listWidgetItem, booklistwidget);

    }
}


//Show details of book in another window
// IMPORTANT: it works if vBooks_ won't be changed in the future,
// TODO?:maybe change it so it will get data from QListWidgetItem(booklistwidget) itself?
void libraryWindowWidget::itemInList_clicked(QListWidgetItem* click)
{
    //qDebug()<<"Item in list clicked";
    //qDebug()<<"Row:"<<ui->listWidget_booksList->row(ui->listWidget_booksList->currentItem());



    int row=ui->listWidget_booksList->row(ui->listWidget_booksList->currentItem());
    bookDetails_ = new BookDetails(vBooks_[row],this);
    //bookDetails_->setModal(false);
    bookDetails_->show();
   // bookDetails_->setFixedSize(bookDetails_->size());
}

//Open Window with advanced searching
void libraryWindowWidget::on_pushButton_wyszukiwanieZaawansowane_clicked()
{
    searchDialog = new Advancedsearch(this);
    searchDialog->setModal(false);
    searchDialog->show();
    searchDialog->setFixedSize(searchDialog->size());
}

void libraryWindowWidget::on_pushButton_clicked()
{
    myAccDialog = new MyAccSettings(this);
    // myAccDialog->setModal(true);
    myAccDialog->show();
    // myAccDialog->setFixedSize(myAccDialog->size());
}

void libraryWindowWidget::on_pushButton_wyszukaj_clicked()
{
    /*
    QJsonObject  book
    {
        {"author",
            QJsonArray{"id","id",
             "name","Alan",
             "removed","false",
             "surname","Raczek"
            }
        },
        {"bookcategory","category"},
        {"description","description"},
        {"id","id"},
        {"keyWords","keyWords"},
        {"name","name"},
        {"releaseDate","releaseDate"},
        {"removed","false"}
    };
*/
    //clear books vector and listWidget
    ui->listWidget_booksList->clear();
    vBooks_.clear();



    //Get everybook from database, assign data to     std::vector<Book> vBooks_;
    QNetworkRequest request(QUrl("http://localhost:8080/book"));
    QNetworkReply *reply = m_nam->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply] {
        reply->deleteLater();
        const QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        const QJsonArray booksArray = jsonDoc.array();
        qDebug()<<"connection succesful, parsing JSON";
        //iterate over every book in array and assign values to variables
        for(QJsonArray::const_iterator itr=booksArray.constBegin();itr!=booksArray.constEnd();++itr)
        {
            QJsonObject book=itr->toObject();
            bool removed = book.value(QString("removed")).toBool();

            //Skip removed books
            if(removed==true) {continue;}

            QJsonObject author=book.value(QString("author")).toObject();

            authorStruct authorStru;
            authorStru.name=author.value(QString("name")).toString();
            authorStru.last_name=author.value(QString("surname")).toString();;
            QString bookID=book.value(QString("id")).toString();
            QString category=book.value(QString("bookcategory")).toString();
            QString title=book.value(QString("name")).toString();
            QString description=book.value(QString("description")).toString();
            QString key_words=book.value(QString("keyWords")).toString();
            QString bookAvail=book.value(QString("bookavailability")).toString();
            QString release_date=book.value(QString("releaseDate")).toString();

            //assign above variables to Book and push Book to vector<Book>
            Book exBook(authorStru,category,title, description, key_words, release_date,bookID,bookAvail);
            //qDebug()<<exBook.title();
            vBooks_.push_back(exBook);
           // qDebug()<<"Size: "<<vBooks_.size();
        }

        //Display books in QListWidget
        displayBooks();
    }
    );
}
