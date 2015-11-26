#ifndef CUSTOMERTABLEMODEL_H
#define CUSTOMERTABLEMODEL_H
#include <QSqlTableModel>
#include <QObject>

class CustomerTableModel : public QSqlTableModel
{
public:
  enum Fields
  {
    ID,
    NAME,
    ADDRESS,
    INTEREST,
    KEY
  };

  CustomerTableModel(QObject *parent, QSqlDatabase *db);
};

#endif // CUSTOMERTABLEMODEL_H
