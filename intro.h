#ifndef INTRO_H
#define INTRO_H

#include <QWidget>
#include"login.h"
namespace Ui {
class intro;
}

class intro : public QWidget
{
    Q_OBJECT

public:
    explicit intro(QWidget *parent = 0);
    ~intro();
private slots:
    void on_pushButton_clicked();
private:
    Ui::intro *ui;
    login * logDialog;
};

#endif // INTRO_H
