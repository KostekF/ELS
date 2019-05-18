#ifndef LIBRARYWINDOWWIDGET_H
#define LIBRARYWINDOWWIDGET_H

#include <QWidget>
#include"QFrame"
#include"Book.h"
#include"vector"
#include<QListWidgetItem>
#include "Bookdetails.h"
#include"Advancedsearch.h"
#include "Myaccsettings.h"
#include<QNetworkAccessManager>
#include"booklistwidget.h"
#include<vector>
namespace Ui {
class libraryWindowWidget;
}

class libraryWindowWidget : public QWidget
{
    Q_OBJECT

public:
    explicit libraryWindowWidget(QWidget *parent = 0);
    ~libraryWindowWidget();

private:
    Ui::libraryWindowWidget *ui;
    QFrame * line;
    std::vector<Book> vBooks_;
    BookDetails * bookDetails_;
    Advancedsearch * searchDialog = nullptr;
    MyAccSettings * myAccDialog = nullptr;
    QNetworkAccessManager * m_nam;
    std::vector<bookListWidget*> vBookListWidgets; //To stop memory leaks
    void readJson(QString json="");
    void displayBooks();  //Display books in QListWidget



public slots:
    void itemInList_clicked(QListWidgetItem* click);
    void on_pushButton_wyszukiwanieZaawansowane_clicked();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_wyszukaj_clicked();
};

#endif // LIBRARYWINDOWWIDGET_H
