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
  bool AuthenticateAdmin(QString username, QString password);
  /// Verify a user login
  bool AuthenticateUser(QString username, QString password);
  /// Purchase an item
  bool Purchase(QString custId, QString prodId);
  /// Add a customer to the database
  bool AddCustomer(QString name, QString address, QString interest, QString key, QString sent);
  /// Add a testimonial to the database
  bool AddTestimonial(QString name, QString testimonial);
  /// Add a user to the database
  bool AddUser(QString id, QString username, QString password);
  /// Remove a customer from the database
  bool RemoveCustomer(QString name);
  /// Set a query
  bool SetQuery(QString newQuery);
  /// Execute query
  bool Exec();
  /// Check if a customer is a key customer
  bool IsKey(QString name);
  /// Check if a table is empty
  bool IsEmpty(QString tableName);
  /// Check if a customer has purchased anything.
  bool HasPurchased(QString id);
  /// Check if a table contains a certain value in a certain field
  bool Contains(QString tableName, QString fieldName, QString value);
  /// Returns the id of the customer with the matching name
  QString GetCustomerIdByName(QString name);
  /// Returns the id of the user with the matching name
  QString GetUserIdByName(QString username);
  /// Retrieve customer name with the matching id
  QString GetCustomerNameById(QString id);
  /// Retrieve customer sent status with with matching id
  QString GetCustomerSentStatus(QString id);
  /// Retrieve all data from a given table
  QList<QSqlRecord>* GetData(QString tableName);

  /// Retrieve all approved testimonials
  QList<QSqlRecord>* GetApprovedTestimonials();


  QString getTestimonialAtIndex(int i);
  QString getImageAtIndex(int i);

private:
  QSqlDatabase *db;
  QSqlQuery query;
};

#endif // DATABASE_H

