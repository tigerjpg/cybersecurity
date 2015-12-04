#include "include/customertablemodel.h"

CustomerTableModel::CustomerTableModel(QObject *parent, QSqlDatabase *db)
                   :QSqlTableModel(parent, *db)
{
  this->setTable("customers");
  this->select();
}

void CustomerTableModel::Initialize()
{
  this->setTable("customers");
  this->setFilter("");
  this->select();
}

void CustomerTableModel::IsKeyToggle()
{
  if (this->filter() == "key == 1")
  {
    this->setFilter("");
  }
  else
  {
    this->setFilter("key == 1");
  }
}
