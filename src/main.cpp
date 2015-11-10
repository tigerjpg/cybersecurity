#include "mainwindow.h"
#include <QApplication>
#include <QtDebug>
#include "../include/database.h"

void TestDatabaseClass();

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;

  TestDatabaseClass();

  w.show();

  return a.exec();
}
