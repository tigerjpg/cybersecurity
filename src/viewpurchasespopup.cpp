#include "viewpurchasespopup.h"
#include "ui_ViewPurchasesPopup.h"

ViewPurchasesPopup::ViewPurchasesPopup(QWidget *parent, Database *db, PurchasesTableModel *model):QWidget(parent),
  ui(new Ui::ViewPurchasesPopup), _model(model)
{
  ui->setupUi(this);
  this->setWindowTitle("View Purchases");
  data = db;
  _model = model;
  ui->purchases_popup_tableView->setModel(_model);
  ui->purchases_popup_tableView->hideColumn(PurchasesTableModel::ID);
  ui->purchases_popup_tableView->verticalHeader()->hide();
  ui->purchases_popup_tableView->resizeColumnsToContents();
  ui->purchases_popup_tableView->horizontalHeader()->setStretchLastSection(true);
}

ViewPurchasesPopup::~ViewPurchasesPopup()
{
  delete ui;
  delete data;
  delete _model;
}

/*!
 * \brief ViewPurchasesPopup::on_purchases_popup_buttonBox_accepted
 * close the popup
 */
void ViewPurchasesPopup::on_purchases_popup_buttonBox_accepted()
{
    close();
}

/*!
 * \brief ViewPurchasesPopup::on_purchases_popup_buttonBox_rejected
 * close the popup
 */
void ViewPurchasesPopup::on_purchases_popup_buttonBox_rejected()
{
    close();
}
