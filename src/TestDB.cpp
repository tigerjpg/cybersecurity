#include "database.h"

/*!
 * \brief TestDB Test functionality and persistence of database
 */
void TestDatabaseClass()
{
  //Test that Database instantiates and opens
  Database *db = new Database("../cybersecurity/data/data.db", "QSQLITE");
  try
  {
    //Check if database is open
    Q_ASSERT(db->isOpen());
    //Remove a default customer.. this will fail if db is not persistent
    Q_ASSERT(db->RemoveCustomer("CIA"));
    //Add the default customer back to prove persistence on next run
    Q_ASSERT(db->AddCustomer("CIA", "987 Jefferson Blvd Baltimore, MD 00754", "2", "true"));
    //Add a test customer to customers
    Q_ASSERT(db->AddCustomer("TestName", "TestAddress", "1", "true"));
    //Remove the test customer from customers
    Q_ASSERT(db->RemoveCustomer("TestName"));
    //Test that "CIA" is a key customer.. it should be
    Q_ASSERT(db->IsKey("CIA"));
    //Test that "Saddleback College" is not a key customer... shouldn't be
    Q_ASSERT(!db->IsKey("Saddleback College"));
    //Test if admins table is empty, should be
    Q_ASSERT(db->IsEmpty("admins"));
    //Test if testimonials table is not empty
    Q_ASSERT(!db->IsEmpty("testimonials"));
    //Test if customers table is empty, should not be
    Q_ASSERT(!db->IsEmpty("customers"));
    //Test if CIA is in customers table
    Q_ASSERT(db->Contains("customers", "name", "CIA"));
    //Test if bart simpson not in customers table (shouldn't be)
    Q_ASSERT(!db->Contains("customers", "name", "bart simpson"));
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
  qDebug() << "Database test successful!";
}
