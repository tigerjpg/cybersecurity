#include "include/customertablemodel.h"

CustomerTableModel::CustomerTableModel(QObject *parent, QSqlDatabase *db):QSqlTableModel(parent, *db)
{
  this->setTable("customers");
  this->select();
}
