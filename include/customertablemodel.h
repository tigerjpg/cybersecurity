#ifndef CUSTOMERTABLEMODEL_H
#define CUSTOMERTABLEMODEL_H
#include <QObject>
#include <QtSql/QtSql>
#include <QSqlTableModel>
#include <QSqlDatabase>

class CustomerTableModel : public QSqlTableModel
{
  Q_OBJECT

public:
  CustomerTableModel(QObject *parent, QSqlDatabase *db);
  QVariant data(const QModelIndex &idx, int role) const;

  void Verify();

  bool IsKey(QString name);


private:
  //    QSqlDatabase db;


};

#endif // CUSTOMERTABLEMODEL_H
