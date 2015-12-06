#-------------------------------------------------
#
# Project created by QtCreator 2015-11-04T19:51:33
#
#-------------------------------------------------

QT       += core gui sql multimedia

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
    src/contactus.cpp \
    src/helpoption.cpp

HEADERS  += include/mainwindow.h \
      include/imagebutton.h \
      include/database.h \
    include/qblowfish_p.h \
    include/qblowfish.h \
    include/contactus.h \
    include/helpoption.h

FORMS    += forms/MainWindow.ui \
    forms/contactus.ui \
    form/helpoption.ui

RESOURCES += \
    cyberresources.qrc
