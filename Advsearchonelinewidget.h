#ifndef ADVSEARCHONELINEWIDGET_H
#define ADVSEARCHONELINEWIDGET_H
#include"Clickablelabel.h"
#include <QDialog>
#include"QListWidgetItem"
namespace Ui {
class AdvSearchOneLineWidget;
}

class AdvSearchOneLineWidget : public QDialog
{
    Q_OBJECT

public:
    explicit AdvSearchOneLineWidget(QWidget *parent = 0);
    AdvSearchOneLineWidget(bool minusHidden,QWidget *parent = 0);
    ~AdvSearchOneLineWidget();


    void hideMinusSign();

private:
    Ui::AdvSearchOneLineWidget *ui;




signals:
    void plusClicked();
    void minusClicked();
private slots:
    void on_widget_plus_clicked();
    void on_widget_minus_clicked();
};

#endif // ADVSEARCHONELINEWIDGET_H
