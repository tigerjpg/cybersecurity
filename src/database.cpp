#include "../include/database.h"
#include <QSqlRecord>
/*!
 * \brief Database::Database constructor
 */
Database::Database()
{
  db = new QSqlDatabase();
  Q_ASSERT(db->open());
}

/*!
 * \brief Database::Database
 * \param path path to sql database file
 */
Database::Database(QString path, QString driver)
{
  db = new QSqlDatabase();
  *db = QSqlDatabase::addDatabase(driver);
  db->setHostName("localhost");
  db->setDatabaseName(path);
  Q_ASSERT(db->open());
  query = QSqlQuery(*db);
}

/*!
 * \brief Database::~Database destructor
 */
Database::~Database()
{

  if(query.isActive())
  {
    query.finish();
    query.clear();
  }
  db->close();
  delete db;

};

/*!
 * \brief Database::AddCustomer Add a customer to the database
 * \param name Customer's name
 * \param address Customer's address
 * \param interest 0 = not interested, 1 = somewhat interested, 2 = very interested
 * \param key true if is key customer
 * \return true if successful
 */
bool Database::AddCustomer(QString name, QString address, QString interest, QString key)
{
  if(key == "true") { key = "1"; }
  else if(key == "false") { key = "0"; }
  return query.exec("insert into customers values(NULL, \"" + name + "\", \"" + address + "\", " + interest + ", " + key +");");
}

/*!
 * \brief Database::RemoveCustomer Remove a customer from the database
 * \param name Customer's name
 * \return true if successful
 */
bool Database::RemoveCustomer(QString name)
{
  return query.exec("delete from customers where name = \"" + name + "\";");
}

/*!
 * \brief Database::SetQuery Prepare a query to be executed
 * \param newQuery A QString SQL query
 * \return true if successfully prepared
 */
bool Database::SetQuery(QString newQuery)
{
  return query.prepare(newQuery);
}

/*!
 * \brief Database::Exec Execute a prepared query
 * \return true if executed successfully
 */
bool Database::Exec()
{
  return query.exec();
}

/*!
 * \brief Database::IsOpen check if db is open
 * \return true if db is open
 */
bool Database::IsOpen()
{
  return db->isOpen();
}

/*!
 * \brief Database::Record
 * Return a QSqlRecord of the current query.
 * This if for use with the QSqlTableModel class.
 * \return QSqlRecord of the current query.
 */
QSqlRecord Database::Record()
{
  return query.record();
}

