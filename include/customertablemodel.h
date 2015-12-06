#ifndef CUSTOMERTABLEMODEL_H
#define CUSTOMERTABLEMODEL_H
#include <QSqlTableModel>
#include <QObject>

class CustomerTableModel : public QSqlTableModel
{
  Q_OBJECT
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

  void Initialize();
  void IsKeyToggle();
};

#endif // CUSTOMERTABLEMODEL_H
