/*
 * This class represents advanced book search dialog window
 *
 *
 *
*/



#ifndef ADVANCEDSEARCH_H
#define ADVANCEDSEARCH_H

#include <QDialog>
#include"Advsearchonelinewidget.h"
#include<QListWidgetItem>
namespace Ui {
class Advancedsearch;
}

class Advancedsearch : public QDialog
{
    Q_OBJECT

public:
    explicit Advancedsearch(QWidget *parent = 0);
    ~Advancedsearch();

private:
    const int maxAdvLineWidgets_=3;
    Ui::Advancedsearch *ui;
    AdvSearchOneLineWidget * advLine;
    int categoriesCounter_;
    AdvSearchOneLineWidget *firstLine=nullptr;
private slots:
    void on_widget_plus_clicked();
    void on_widget_minus_clicked(QWidget * widget);
    void on_listWidget_categories_itemClicked(QListWidgetItem* item);
    void on_pushButton_wyszukaj_clicked();
};


#endif // ADVANCEDSEARCH_H
