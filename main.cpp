#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include<string>


bool isLogged=false;

//QString g_userID="5cf16f3107a4bc0a80479e13"; //TODO: DELETE THIS!
QString g_userID;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
