#ifndef VIEWPURCHASESPOPUP_H
#define VIEWPURCHASESPOPUP_H
#include "database.h"
#include "purchasestablemodel.h"
#include <QWidget>

namespace Ui {
class ViewPurchasesPopup;
}

/*!
 * \brief The ViewPurchasesPopup class
 * is a popup window for viewing a specific customers purchases.
 */
class ViewPurchasesPopup : public QWidget
{
  Q_OBJECT

public:
  explicit ViewPurchasesPopup(QWidget *parent = 0, Database *db = 0, PurchasesTableModel *model = 0);
  ~ViewPurchasesPopup();

private slots:
  void on_purchases_popup_buttonBox_accepted();

  void on_purchases_popup_buttonBox_rejected();

private:
  Ui::ViewPurchasesPopup *ui;
  PurchasesTableModel *_model;
  Database *data;
};

#endif // VIEWPURCHASESPOPUP_H
