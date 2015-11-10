#include <QtTest/QtTest>
#include <QSqlDatabase>
#include <QSqlQuery>
class TestDatabase : public QObject, QSqlDatabase
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
};

TestDatabase::TestDatabase():QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))
{
  setHostName("localhost");
  setDatabaseName("../cybersecurity/data/data.db");
  open();
}

TestDatabase::~TestDatabase()
{
  close();
}

void TestDatabase::TestOpen()
{
  QVERIFY(open());
}

void TestDatabase::TestTables()
{
  query = new QSqlQuery(this->database());
  QVERIFY(query->exec("select * from customers"));
  QVERIFY(query->exec("select * from admins"));
  QVERIFY(query->exec("select * from pamphlets"));
  QVERIFY(query->exec("select * from testimonials"));
}

QTEST_MAIN(TestDatabase)
#include "testdatabase.moc"