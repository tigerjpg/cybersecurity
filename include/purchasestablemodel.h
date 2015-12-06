#ifndef PURCHASESTABLEMODEL_H
#define PURCHASESTABLEMODEL_H
#include <QSqlTableModel>
#include <QSqlDatabase>

class PurchasesTableModel : public QSqlTableModel
{
  Q_OBJECT
public:
  ///Fields for Purchases table
  enum Field
  {
    ID,
    CUSTNAME,
    PRODNAME,
    PRICE
  };

  PurchasesTableModel(QObject *parent, QSqlDatabase *db, int customer);

  ///Initialize settings for PurchasesTableModel
  void Initialize();
};

#endif // PURCHASESTABLEMODEL_H
