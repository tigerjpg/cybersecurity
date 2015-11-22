#include "customertablemodel.h"
#include <iostream>




CustomerTableModel::CustomerTableModel(QObject *parent, QSqlDatabase *db) :
  QSqlTableModel(parent, *db)
{
  this->setTable("customers");
  this->select();
}

QVariant CustomerTableModel::data(const QModelIndex &idx, int role) const
{
  QString str;
  if (role == Qt::DisplayRole)
  {
    QSqlTableModel asdf;
    //asdf.set
  }
  return str;
}

void CustomerTableModel::Verify()
{

}

bool CustomerTableModel::IsKey(QString name)
{
  this->query().exec("select key from customers where name = \"" + name + "\";");
  return this->query().first();
}