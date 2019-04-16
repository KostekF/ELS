#ifndef LIBRARYWINDOWWIDGET_H
#define LIBRARYWINDOWWIDGET_H

#include <QWidget>
#include"QFrame"
#include"Book.h"
#include"vector"
#include<QListWidgetItem>
#include "Bookdetails.h"
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

    void readJson(QString json="");

public slots:
    void itemInList_clicked(QListWidgetItem* click);
};

#endif // LIBRARYWINDOWWIDGET_H
