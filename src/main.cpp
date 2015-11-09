#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QException>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  QSqlDatabase *db = new QSqlDatabase();
  *db = QSqlDatabase::addDatabase("QSQLITE");
  db->setHostName("localhost");
  db->setDatabaseName("../data/data.db");

  //Open database
  Q_ASSERT(db->open());
  QSqlQuery query;
  //Get all info from table customers
  Q_ASSERT(query.exec("select * from customers;"));
  while(query.next())
  {
    int customerId = query.value("id").toInt();
    QString name = query.value("name").toString();
    QString address = query.value("address").toString();
    int interest = query.value("interest").toInt();
    bool isKey = query.value("key").toBool();
    qDebug() << customerId << name << ' ' << address << ' ' << interest << ' ' << isKey;
  }

  Q_ASSERT(query.exec("select * from admins"));
  while(query.next())
  {
    QString name = query.value(0).toString();
    QString pass = query.value(1).toString();
    qDebug() << name << ' ' << pass;
  }

  //add to database
  Q_ASSERT(query.exec("insert into customers values (NULL, \"jesse\", \"7 hazelbranch\", 2, 1);"));

  //print database
  Q_ASSERT(query.exec("select * from customers;"));
  while(query.next())
  {
    int customerId = query.value("id").toInt();
    QString name = query.value("name").toString();
    QString address = query.value("address").toString();
    int interest = query.value("interest").toInt();
    bool isKey = query.value("key").toBool();
    qDebug() << customerId << name << ' ' << address << ' ' << interest << ' ' << isKey;
  }


  w.show();

  return a.exec();
}
