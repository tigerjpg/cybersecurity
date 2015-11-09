#include "mainwindow.h"
#include <QApplication>
#include <QtDebug>
#include "../include/database.h"

bool TestDatabaseClass();

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;

  if(TestDatabaseClass())
  {
    qDebug() << "Database test successful!";
  }
  else
  {
    qDebug() << "Database test failed!";
  }

  w.show();

  return a.exec();
}
