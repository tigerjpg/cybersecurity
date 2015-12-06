#ifndef CUSTOMERTABLEMODEL_H
#define CUSTOMERTABLEMODEL_H
#include <QSqlTableModel>
#include <QObject>

class CustomerTableModel : public QSqlTableModel
{
  Q_OBJECT
public:
  ///Fields in the Customer Table
  enum Fields
  {
    ID,
    NAME,
    ADDRESS,
    INTEREST,
    KEY,
    SENT
  };

  CustomerTableModel(QObject *parent, QSqlDatabase *db);

  ///Initialize model settings
  void Initialize();
  ///Set customer to key customer or not
  void IsKeyToggle();
};

#endif // CUSTOMERTABLEMODEL_H
