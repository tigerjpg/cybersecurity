#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QList>
/*!
 * \brief The Database class is a wrapper for QSqlDatabase
 */
class Database
{
public:
  ///Create database with defaults
  Database();
  ///Create database from specified db file and driver
  Database(QString path, QString driver);
  ///Destructor
  ~Database();

  ///Add a customer to the database
  bool AddCustomer(QString name, QString address, QString interest, QString key);
  ///Remove a customer from the database
  bool RemoveCustomer(QString name);
  ///Set a query
  bool SetQuery(QString newQuery);
  ///Execute query
  bool Exec();
  ///Check if DB is open
  bool IsOpen();
  ///Return a QSqlRecord of the current query
  QSqlRecord Record();

private:
  QSqlDatabase *db;
  QSqlQuery query;
};

#endif // DATABASE_H

