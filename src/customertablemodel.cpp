#include "include/customertablemodel.h"

CustomerTableModel::CustomerTableModel(QObject *parent, QSqlDatabase *db)
                   :QSqlTableModel(parent, *db)
{
  this->setEditStrategy(QSqlTableModel::OnManualSubmit);
  this->setTable("customers");
  this->setHeaderData(ID, Qt::Horizontal, tr("ID"), QSqlTableModel::OnManualSubmit);
  this->setHeaderData(NAME, Qt::Horizontal, tr("Name"), QSqlTableModel::OnManualSubmit);
  this->setHeaderData(ADDRESS, Qt::Horizontal, tr("Address"), QSqlTableModel::OnManualSubmit);
  this->setHeaderData(KEY, Qt::Horizontal, tr("Key"), QSqlTableModel::OnManualSubmit);
  this->setHeaderData(INTEREST, Qt::Horizontal, tr("Interest"), QSqlTableModel::OnManualSubmit);
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
