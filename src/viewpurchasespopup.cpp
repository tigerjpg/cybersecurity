#include "viewpurchasespopup.h"
#include "ui_ViewPurchasesPopup.h"

ViewPurchasesPopup::ViewPurchasesPopup(QWidget *parent, Database *db, PurchasesTableModel *model):QWidget(parent),
  ui(new Ui::ViewPurchasesPopup), _model(model)
{
  ui->setupUi(this);
  this->setWindowTitle("View Purchases");
  data = db;
  ui->purchases_popup_tableView->setModel(model);
  ui->purchases_popup_tableView->hideColumn(PurchasesTableModel::ID);
  ui->purchases_popup_tableView->verticalHeader()->hide();
  ui->purchases_popup_tableView->resizeColumnsToContents();
  ui->purchases_popup_tableView->horizontalHeader()->setStretchLastSection(true);
}

ViewPurchasesPopup::~ViewPurchasesPopup()
{
  delete ui;
  delete data;
}

void ViewPurchasesPopup::on_purchases_popup_buttonBox_accepted()
{
    close();
}

void ViewPurchasesPopup::on_purchases_popup_buttonBox_rejected()
{
    close();
}
