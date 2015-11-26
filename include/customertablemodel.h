#ifndef CUSTOMERTABLEMODEL_H
#define CUSTOMERTABLEMODEL_H
#include <QSqlTableModel>
#include <QObject>

class CustomerTableModel : public QSqlTableModel
{
public:
  CustomerTableModel(QObject *parent, QSqlDatabase *db);
};

#endif // CUSTOMERTABLEMODEL_H
