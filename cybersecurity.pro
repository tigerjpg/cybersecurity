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
		   src/imagebutton.cpp \
		   src/database.cpp \
    src/qblowfish.cpp \
    src/customertablemodel.cpp

HEADERS  += include/mainwindow.h \
      include/imagebutton.h \
      include/database.h \
    include/qblowfish_p.h \
    include/qblowfish.h \
    include/customertablemodel.h

FORMS    += forms/MainWindow.ui

RESOURCES += \
    cyberresources.qrc
