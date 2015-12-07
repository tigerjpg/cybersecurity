#ifndef ADDCUSTOMERPOPUP_H
#define ADDCUSTOMERPOPUP_H
#include "database.h"
#include "customertablemodel.h"
#include "errorpopup.h"
#include <QWidget>

namespace Ui {
class AddCustomerPopup;
}

/*!
 * \brief The AddCustomerPopup class is a popup for adding customers
 */
class AddCustomerPopup : public QWidget
{
  Q_OBJECT

public:
  explicit AddCustomerPopup(QWidget *parent = 0, Database *db = 0, CustomerTableModel *cTableModel = 0);
  ~AddCustomerPopup();

private slots:
  void on_add_customer_buttonBox_accepted();

  void on_add_customer_buttonBox_rejected();

private:
  Ui::AddCustomerPopup *ui;
  CustomerTableModel *model;
  Database *data;
};

#endif // ADDCUSTOMERPOPUP_H
