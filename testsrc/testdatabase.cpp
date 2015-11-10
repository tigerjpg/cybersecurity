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

QTEST_MAIN(TestDatabase)
#include "testdatabase.moc"