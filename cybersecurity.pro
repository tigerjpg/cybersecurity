#-------------------------------------------------
#
# Project created by QtCreator 2015-11-04T19:51:33
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cybersecurity
TEMPLATE = app

DEPENDPATH += src
INCLUDEPATH += include

SOURCES += src/main.cpp \
           src/mainwindow.cpp \
    src/imagebutton.cpp

HEADERS  += include/mainwindow.h \
    include/imagebutton.h

FORMS    += forms/MainWindow.ui

RESOURCES += \
    cyberresources.qrc
