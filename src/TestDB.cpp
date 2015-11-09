#include "../include/database.h"

/*!
 * \brief TestDB
 * \param db
 */
bool TestDatabaseClass()
{
  Database *db = new Database("../data/data.db", "QSQLITE");
  try
  {
    //Check if database is open
    Q_ASSERT(db->IsOpen());
    //remove customer added on last test run
    Q_ASSERT(db->RemoveCustomer("Persistence Proof"));
    //Add a test customer to customers
    Q_ASSERT(db->AddCustomer("TestName", "TestAddress", "1", "1"));
    //Remove the test customer from customers
    Q_ASSERT(db->RemoveCustomer("TestName"));
    //Add a customer that will be removed upon next run
    Q_ASSERT(db->AddCustomer("Persistence Proof", "address", "0", "0"));
    //Test that "CIA" is a key customer.. it should be
    Q_ASSERT(db->IsKey("CIA"));
    //Test that "Saddleback College" is not a key customer... shouldn't be
    Q_ASSERT(!db->IsKey("Saddleback College"));
    //Test if admins table is empty, should be
    db->IsEmpty("admins");
    //Test if customers table is empty, should not be
    Q_ASSERT(!db->IsEmpty("customers"));
  }
  catch(Database::InvalidTableName)
  {
    qDebug() << "Invalid Table Name\n";
  }
  catch(Database::InvalidQuery)
  {
    qDebug() << "Invalid Query\n";
  }
  catch(Database::EmptyQuery)
  {
    qDebug() << "Empty Query\n";
  }

  delete db;

  return true;
}
