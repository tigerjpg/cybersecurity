#include <QtTest/QtTest>
#include "database.h"
/*!
 * \brief The TestDatabase class is a unit test for the Database class
 */
class TestDatabase : public QObject
{
  Q_OBJECT
public:
  ///Constructor
  TestDatabase();
  ///Destructor
  ~TestDatabase();
private slots:
  void TestOpen();
  void TestTables();
  void TestAddCustomers();
  void TestRemoveCustomers();
  void TestIsKey();
private:
  QSqlQuery *query;
  Database *db;
};

TestDatabase::TestDatabase()
{
  //Initialize Database object
  db = new Database("../cybersecurity/data/data.db", "QSQLITE");
}

TestDatabase::~TestDatabase()
{
  //Close database
  db->close();
}

/*!
 * \brief TestDatabase::TestOpen
 * Verify that the Database file is successfully opened.
 */
void TestDatabase::TestOpen()
{
  QVERIFY(db->isOpen());
}

/*!
 * \brief TestDatabase::TestTables
 * Tests that the tables exist in the SQL database
 */
void TestDatabase::TestTables()
{
  QVERIFY(db->SetQuery("select * from customers"));
  QVERIFY(db->Exec());
  QVERIFY(db->SetQuery("select * from admins"));
  QVERIFY(db->Exec());
  QVERIFY(db->SetQuery("select * from testimonials"));
  QVERIFY(db->Exec());
  QVERIFY(db->SetQuery("select * from pamphlets"));
  QVERIFY(db->Exec());
}

/*!
 * \brief TestDatabase::TestAddCustomers
 * Test the AddCustomer method by adding a valid test customer,
 * removing it, and attempting to add an invalid test customer.
 */
void TestDatabase::TestAddCustomers()
{
  try
  {
    QVERIFY(db->AddCustomer("TEST", "TESTADDRESS", "2", "1"));
    QVERIFY(!db->AddCustomer("TEST", "TESTADDRESS", "2", "1"));
    QVERIFY(!db->AddCustomer("invalid interest value", "123 fake street",
                             "5", "0"));
  }
  catch (Database::InvalidQuery)
  {
    qDebug() << "Invalid Query";
  }
  catch (Database::InvalidTableName)
  {
    qDebug() << "Invalid Table Name";
  }
  catch (Database::EmptyQuery)
  {
    qDebug() << "Empty Query";
  }
}

/*!
 * \brief TestDatabase::TestRemoveCustomers
 * Test the RemoveCustomer method by removing the test customer
 * added in the previous test.
 */
void TestDatabase::TestRemoveCustomers()
{
  QVERIFY(db->RemoveCustomer("TEST"));
}

/*!
 * \brief TestDatabase::TestIsKey
 * Test the IsKey method by checking true and false conditions.
 */
void TestDatabase::TestIsKey()
{
  try
  {
    QCOMPARE(db->IsKey("CIA"), 1);
    QCOMPARE(db->IsKey("bart simpson"), 0);
    QCOMPARE(db->IsKey("bart simpson"), 1);
    QCOMPARE(db->IsKey("Saddleback College"), 0);
  }
  catch(Database::EmptyQuery)
  {
    qDebug() << "Empty Query";
  }
  catch(Database::InvalidQuery)
  {
    qDebug() << "Invalid Query";
  }
}

QTEST_MAIN(TestDatabase)
#include "testdatabase.moc"