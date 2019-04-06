#ifndef LIBRARYWINDOWWIDGET_H
#define LIBRARYWINDOWWIDGET_H

#include <QWidget>
#include"QFrame"
#include"Book.h"
#include"vector"
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


    void readJson(QString json="");
};

#endif // LIBRARYWINDOWWIDGET_H
