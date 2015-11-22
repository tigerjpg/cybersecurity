#include "../include/database.h"
/*!
 * \brief Database::Database constructor
 */
Database::Database(){}

/*!
 * \brief Database::Database
 * \param path path to sql database file
 */
Database::Database(QString path, QString driver) : QSqlDatabase(addDatabase(driver))
{
  setHostName("localhost");
  setDatabaseName(path);
  if(!open())
  {
    qDebug() << lastError();
  }
  query = QSqlQuery(*this);
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
  close();
}

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
  if(query.exec("insert into customers values(NULL, \"" + name +
                "\", \"" + address + "\", " + interest + ", " + key +");"))
    return true;
  else
  {
    qDebug() << query.lastError().text();
    throw InvalidQuery();
  }
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
 * \brief Database::IsKey Check if a customer is a key customer or not
 * \param name
 * \return true if customer is a key customer
 */
bool Database::IsKey(QString name)
{
  //execute query
  if(this->query.exec("select * from customers where name = \""
                + name + "\";"))
    //if there is data in the query
    if(query.next())
    {
      //get info from "key" field in this record
      return (query.record().field("key").value().toBool());
    }
    else
    {
      qDebug() << query.lastError().text();
      throw EmptyQuery();
    }
  else
  {
    qDebug() << query.lastError().text();
    throw InvalidQuery();
  }
}

/*!
 * \brief Database::IsEmpty Check if a table is empty
 * \param tableName
 * \return true if table is empty
 */
bool Database::IsEmpty(QString tableName)
{
  if(query.exec("select * from " + tableName + ";"))
    return !query.next();
  else
  {
    qDebug() << query.lastError().text();
    throw InvalidTableName();
  }
}

/*!
 * \brief Database::Contains
 * Check if a certain value exists in a certain field in a table
 * \param tableName
 * \param fieldName
 * \param value
 * \return true if value exists in field of table
 */
bool Database::Contains(QString tableName, QString fieldName, QString value)
{
  if(query.exec("select * from \"" + tableName +
                "\" where \"" + fieldName + "\" = \"" + value + "\";"))
  {
    return query.next();
  }
  else
  {
    qDebug() << query.lastError().text();
    throw InvalidQuery();
  }
}
