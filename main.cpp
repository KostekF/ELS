#include "mainwindow.h"
#include <QApplication>
#include <QLabel>



bool isLogged=false;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
