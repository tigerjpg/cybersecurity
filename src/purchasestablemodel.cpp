#include "purchasestablemodel.h"
#include <QDebug>
PurchasesTableModel::PurchasesTableModel(QObject *parent, QSqlDatabase *db, int customer):
                                         QSqlTableModel(parent, *db)
{
  QString id = QString::number(customer);
  this->setTable("purchasesView");
  this->setFilter("id = " + id);
  Initialize();
  this->select();
}

/*!
 * \brief PurchasesTableModel::Initialize
 * Initialize settings for PurchasesTableModel
 */
void PurchasesTableModel::Initialize()
{
  this->setHeaderData(CUSTNAME, Qt::Horizontal, tr("Customer Name"), QSqlTableModel::OnManualSubmit);
  this->setHeaderData(PRODNAME, Qt::Horizontal, tr("Product Name"), QSqlTableModel::OnManualSubmit);
  this->setHeaderData(PRICE, Qt::Horizontal, tr("Price"), QSqlTableModel::OnManualSubmit);
}
