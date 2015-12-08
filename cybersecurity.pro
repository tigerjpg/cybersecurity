#-------------------------------------------------
#
# Project created by QtCreator 2015-11-04T19:51:33
#
#-------------------------------------------------

QT       += core gui sql multimedia webkit webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cybersecurity
TEMPLATE = app

DEPENDPATH += src
INCLUDEPATH += include

SOURCES += src/main.cpp \
       src/imagebutton.cpp \
       src/database.cpp \
    src/qblowfish.cpp \
    src/contactus.cpp \
    src/helpoption.cpp \
    src/customertablemodel.cpp \
    src/mainwindow.cpp \
    src/testimonialtablemodel.cpp \
    src/addtestimonialpopup.cpp \
    src/viewpurchasespopup.cpp \
    src/purchasestablemodel.cpp \
    src/addcustomerpopup.cpp \
    src/errorpopup.cpp


HEADERS  += include/mainwindow.h \
      include/imagebutton.h \
      include/database.h \
    include/qblowfish_p.h \
    include/qblowfish.h \
    include/contactus.h \
    include/helpoption.h \
    include/customertablemodel.h \
    include/testimonialtablemodel.h \
    include/addtestimonialpopup.h \
    include/viewpurchasespopup.h \
    include/purchasestablemodel.h \
    include/addcustomerpopup.h \
    include/contactus.h \
    include/errorpopup.h

FORMS    += forms/MainWindow.ui \
    forms/contactus.ui \
    forms/helpoption.ui \
    forms/AddTestimonialPopup.ui \
    forms/ViewPurchasesPopup.ui \
    forms/AddCustomerPopup.ui \
    forms/contactus.ui \
    forms/errorpopup.ui

RESOURCES += \
    cybersounds.qrc \
    cyberhtml.qrc \
    cyberimages.qrc \
    cyberbuttonigmages.qrc


