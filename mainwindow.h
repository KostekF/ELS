#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"librarywindowwidget.h"
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

private:
    Ui::MainWindow *ui;
    libraryWindowWidget * libWindow;
};

#endif // MAINWINDOW_H
