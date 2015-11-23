#include "mainwindow.h"
#include <QApplication>
#include <QtDebug>
#include "database.h"

// Test class for initializing and testing the database
void TestDatabaseClass();

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;

  w.show();

  return a.exec();
}
