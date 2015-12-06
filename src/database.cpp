#include "database.h"
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
  open();
  query = QSqlQuery(*this);
  query.exec("PRAGMA foreign_keys = ON;");
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
 * \brief Database::Authenticate
 * Verifies admin credentials. Uses blowfish encryption algorithm.
 * \param username
 * \param password
 * \return true if admin exists with these credentials
 */
bool Database::Authenticate(QString username, QString password)
{
  QBlowfish bf(QByteArray::fromHex(KEY_HEX));
  bf.setPaddingEnabled(true);
  QByteArray encryptedAr = bf.encrypted(password.toUtf8());
  QString encryptedStr = encryptedAr.toHex();
  query.exec("select * from admins where username = \""
                    + username + "\" and password = \""
                    + encryptedStr + "\";");
  return query.next();
}

/*!
 * \brief Database::AddCustomer Add a customer to the database
 * \param name Customer's name
 * \param address Customer's address
 * \param interest 0 = not interested, 1 = somewhat interested, 2 = very interested
 * \param key true if is key customer
 * \return true if successful
 */
bool Database::AddCustomer(QString name, QString address, QString interest, QString key, QString sent)
{
  if(key == "true") { key = "1"; }
  else if(key == "false") { key = "0"; }
  if(query.exec("insert into customers values(NULL, \"" + name +
                "\", \"" + address + "\", " + interest + ", "
                + key + ", " + sent + ");"))
    return true;
  else
  {
    qDebug() << query.lastError().text();
    throw InvalidQuery();
  }
}

/*!
 * \brief Database::AddTestimonial
 * \param name
 * \param testimonial
 * \return
 */
bool Database::AddTestimonial(QString name, QString testimonial)
{
  if(query.exec("insert into testimonials values(NULL, \"" + name
                + "\", \"" + testimonial + "\", NULL, 0);"))
  {
    return true;
  }
  else
  {
    qDebug() << query.lastError().text();
    throw InvalidQuery();
  }
}
/*!
 * \brief Database::AddUser Add a user to the database
 * \param username user's username
 * \param password user's password
 * \param key true if is administrator
 * \return true if successful
 */
bool Database::AddUser(QString id, QString username, QString password, QString admin)
{
  QBlowfish bf(QByteArray::fromHex(KEY_HEX));
  bf.setPaddingEnabled(true);
  QByteArray encryptedAr = bf.encrypted(password.toUtf8());
  QString encryptedStr = encryptedAr.toHex();

  if(admin == "true") { admin = "1"; }
  else if(admin == "false") { admin = "0"; }
  if(query.exec("insert into users values(\"" + id +
                "\", \"" + username + "\", \"" + encryptedStr + "\", 0);"))
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

/*!
 * \brief Database::GetCustomerIdByName
 * \param name
 * \return the id of the customer
 */
QString Database::GetCustomerIdByName(QString name)
{
  if(query.exec("select id from customers where name = \"" + name + "\";"))
  {
    if(query.next())
    {
      return query.record().field("id").value().toString();
    }
    else
    {
      qDebug() << query.lastError().text();
      throw InvalidQuery();
    }
  }
  else
  {
    qDebug() << query.lastError().text();
    throw InvalidQuery();
  }
}

QString Database::GetUserIdByName(QString username)
{
  if(query.exec("select id from users where username = \"" + username + "\";"))
  {
    if(query.next())
    {
      return query.record().field("id").value().toString();
    }
    else
    {
      qDebug() << query.lastError().text();
      throw InvalidQuery();
    }
  }
  else
  {
    qDebug() << query.lastError().text();
    throw InvalidQuery();
  }
}

/*!
 * \brief Database::GetData
 * Get a QList of all records in a specified table.
 * \param tableName The name of the table to retrieve data from
 * \return QList<QSqlRecord> containing all records in table
 */
QList<QSqlRecord> * Database::GetData(QString tableName)
{
  QList<QSqlRecord> *list = new QList<QSqlRecord>;
  if(query.exec("select * from \"" + tableName +"\";"))
    {
      while(query.next())
        {
          list->push_back(query.record());
        }
    }
  else
    {
      qDebug() << "INVALID QUERY!";
    }
  return list;
}

/*!
 * \brief Database::getTestimonialAtIndex
 * \param i index
 * \return The testimonial at a specific index
 */
QString Database::getTestimonialAtIndex(int i)
{
  QString id = QString::number(i);
  if(this->query.exec("select testimonial from testimonials where id = \"" + id + "\";"))
    {
      if(query.next())
        {
          return query.record().field("testimonial").value().toString();
        }
    }
  return "Woops!";
}

/*!
 * \brief Database::getImageAtIndex
 * \param i
 * \return image name at a specified index
 */
QString Database::getImageAtIndex(int i)
{
  QString id = QString::number(i);
  if(this->query.exec("select image from testimonials where id = \"" + id + "\";"))
    {
      if(query.next())
        {
          return query.record().field("image").value().toString();
        }
    }
  return "Woops!";
}
