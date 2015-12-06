#ifndef PURCHASESTABLEMODEL_H
#define PURCHASESTABLEMODEL_H
#include <QSqlTableModel>
#include <QSqlDatabase>

class PurchasesTableModel : public QSqlTableModel
{
  Q_OBJECT
public:
  enum Field
  {
    ID,
    CUSTNAME,
    PRODNAME,
    PRICE
  };

  PurchasesTableModel(QObject *parent, QSqlDatabase *db, int customer);

  void Initialize();
};

#endif // PURCHASESTABLEMODEL_H
