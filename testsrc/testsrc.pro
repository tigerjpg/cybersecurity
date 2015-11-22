#-------------------------------------------------
#
# Project created by QtCreator 2015-11-04T19:51:33
#
#-------------------------------------------------

QT       += core gui sql testlib

TARGET = test
TEMPLATE = app
DEPENDPATH += ../src \ ../testsrc
INCLUDEPATH += include

SOURCES += ../src/database.cpp \
       ../testsrc/testdatabase.cpp

HEADERS  += ../include/database.h

FORMS    += 

RESOURCES += ../cyberresources.qrc

