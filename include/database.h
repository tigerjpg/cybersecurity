#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
#include <QException>
#include <QList>
#include "qblowfish.h"
#define KEY_HEX "0d3dd5d20734921c01bd78179fabf9ac"

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

  /// Verify an admin login
  bool Authenticate(QString username, QString password);
  ///Add a customer to the database
  bool AddCustomer(QString name, QString address, QString interest, QString key);
  ///Add a user to the database
  bool AddUser(QString id, QString username, QString password, QString admin);
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
  ///Returns the id of the customer with the matching name
  QString GetCustomerIdByName(QString name);

  QList<QSqlRecord> GetData(QString tableName);


  QString getTestimonialAtIndex(int i);
  QString getImageAtIndex(int i);

private:
  QSqlDatabase *db;
  QSqlQuery query;
};

#endif // DATABASE_H

