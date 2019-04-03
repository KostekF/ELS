#-------------------------------------------------
#
# Project created by QtCreator 2019-03-26T21:47:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ELS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    intro.cpp \
    librarywindowwidget.cpp

HEADERS  += mainwindow.h \
    login.h \
    intro.h \
    librarywindowwidget.h

FORMS    += mainwindow.ui \
    login.ui \
    intro.ui \
    librarywindowwidget.ui

RESOURCES += \
    resources.qrc
