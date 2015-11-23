#include "mainwindow.h"
#include <QApplication>
#include <QtDebug>
#include "database.h"
#include "qblowfish.h"


// Test class for initializing and testing the database
//void TestDatabaseClass();

int main(int argc, char *argv[])
{

  Database *db = new Database("./data/data.db", "QSQLITE");
  qDebug() << db->open();

  //verifying admin credentials - true condition
  qDebug() << db->Authenticate("tiger", "meow420");
  //verifying admin credentials - false condition
  qDebug() << db->Authenticate("tiger", "meow421");

  QApplication a(argc, argv);
  MainWindow w;

  w.show();

  return a.exec();
}
