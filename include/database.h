#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
#include <QException>

/*!
 * \brief The Database class is a wrapper for QSqlDatabase
 */
class Database : public QSqlDatabase
{
public:
  ///Create database with defaults
  Database();
  ///Create database from specified db file and driver
  Database(QString path, QString driver);
  ///Destructor
  ~Database();

  ///Exception class
  class InvalidTableName : public QException{};
  ///Exception class
  class InvalidQuery     : public QException{};
  ///Exception class
  class EmptyQuery       : public QException{};

  ///Add a customer to the database
  bool AddCustomer(QString name, QString address, QString interest, QString key);
  ///Remove a customer from the database
  bool RemoveCustomer(QString name);
  ///Set a query
  bool SetQuery(QString newQuery);
  ///Execute query
  bool Exec();
  ///Check if a customer is a key customer
  bool IsKey(QString name);
  ///Check if a table is empty
  bool IsEmpty(QString tableName);
  ///Check if a table contains a certain value in a certain field
  bool Contains(QString tableName, QString fieldName, QString value);

private:
  QSqlDatabase *db;
  QSqlQuery query;
};

#endif // DATABASE_H

