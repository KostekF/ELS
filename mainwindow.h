#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"librarywindowwidget.h"
#include"intro.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void showLibWindow();
    void returnToIntroWindow();

private slots:
    void on_actionPanel_operatorski_triggered();

private:
    Ui::MainWindow *ui;
    libraryWindowWidget * libWindow;
    intro * introWindow;
};

#endif // MAINWINDOW_H
