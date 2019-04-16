#ifndef BOOKLISTWIDGET_H
#define BOOKLISTWIDGET_H

#include <QWidget>
#include"Book.h"
namespace Ui {
class bookListWidget;
}

class bookListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit bookListWidget(QWidget *parent = 0);
    ~bookListWidget();

    void setMainTitle(QString author, QString title);
    void setLabelPhoto(QString resAddress);
    void setDescription(QString description);
    void setKeywords(QString keywords);



private:
    Ui::bookListWidget *ui;
};

#endif // BOOKLISTWIDGET_H
