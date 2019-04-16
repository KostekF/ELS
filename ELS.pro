#-------------------------------------------------
#
# Project created by QtCreator 2019-03-26T21:47:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ELS
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    intro.cpp \
    librarywindowwidget.cpp \
    Book.cpp \
    booklistwidget.cpp \
    Register.cpp \
    Clickablelabel.cpp \
    Resetpassword.cpp \
    Bookdetails.cpp \
    Advancedsearch.cpp \
    Advsearchonelinewidget.cpp

HEADERS  += mainwindow.h \
    login.h \
    intro.h \
    librarywindowwidget.h \
    Book.h \
    booklistwidget.h \
    Register.h \
    Clickablelabel.h \
    Resetpassword.h \
    Bookdetails.h \
    Advancedsearch.h \
    Advsearchonelinewidget.h

FORMS    += mainwindow.ui \
    login.ui \
    intro.ui \
    librarywindowwidget.ui \
    booklistwidget.ui \
    Register.ui \
    Resetpassword.ui \
    Bookdetails.ui \
    Advancedsearch.ui \
    Advsearchonelinewidget.ui

RESOURCES += \
    resources.qrc

DISTFILES +=
