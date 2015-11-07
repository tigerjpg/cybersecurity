#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  QSqlDatabase *db = new QSqlDatabase();
  *db = QSqlDatabase::addDatabase("QSQLITE");
  db->setHostName("localhost");
  db->setDatabaseName("../data/data.db");

  Q_ASSERT(db->open());
  QSqlQuery query;
  Q_ASSERT(query.exec("select * from customers;"));
  while(query.next())
  {
    QString name = query.value(0).toString();
    QString address = query.value(1).toString();
    QString interest = query.value(2).toString();
    bool isKey = query.value(3).toBool();
    qDebug() << name << ' ' << address << ' ' << interest << ' ' << isKey;
  }
  w.show();

  return a.exec();
}
