#include <QtTest/QtTest>
#include "database.h"
class TestDatabase : public QObject
{
  Q_OBJECT
public:
  TestDatabase();
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
  db = new Database("../cybersecurity/data/data.db", "QSQLITE");
}

TestDatabase::~TestDatabase()
{
  db->close();
}

void TestDatabase::TestOpen()
{
  QVERIFY(db->isOpen());
}

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

void TestDatabase::TestRemoveCustomers()
{
  QVERIFY(db->RemoveCustomer("TEST"));
}

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