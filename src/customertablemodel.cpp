#include "include/customertablemodel.h"

CustomerTableModel::CustomerTableModel(QObject *parent, QSqlDatabase *db)
                   :QSqlTableModel(parent, *db)
{
  Initialize();
}

/*!
 * \brief CustomerTableModel::Initialize
 * Set the table to display and all column labels.
 */
void CustomerTableModel::Initialize()
{
  this->setEditStrategy(QSqlTableModel::OnManualSubmit);
  this->setTable("customers");
  this->setHeaderData(ID, Qt::Horizontal, tr("ID"), QSqlTableModel::OnManualSubmit);
  this->setHeaderData(NAME, Qt::Horizontal, tr("Name"), QSqlTableModel::OnManualSubmit);
  this->setHeaderData(ADDRESS, Qt::Horizontal, tr("Address"), QSqlTableModel::OnManualSubmit);
  this->setHeaderData(KEY, Qt::Horizontal, tr("Key"), QSqlTableModel::OnManualSubmit);
  this->setHeaderData(INTEREST, Qt::Horizontal, tr("Interest"), QSqlTableModel::OnManualSubmit);
  this->setHeaderData(SENT, Qt::Horizontal, tr("Pamphlet Sent"), QSqlTableModel::OnManualSubmit);
  this->setFilter("");
  this->select();
}

/*!
 * \brief CustomerTableModel::IsKeyToggle
 * If a customer is a key customer, set them to not be a key customer.
 * If a customer is not a key customer, make them a key customer.
 */
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
