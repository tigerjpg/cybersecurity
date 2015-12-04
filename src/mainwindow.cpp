#include "mainwindow.h"
#include "ui_MainWindow.h"
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  db = new Database("./data/data.db", "QSQLITE");


}
MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_login_buttonBox_accepted()
{
  if(!ui->username_line->text().isEmpty() && !ui->password_line->text().isEmpty())
  {
    if(db->Authenticate(ui->username_line->text(), ui->password_line->text()))
    {
      cTableModel = new CustomerTableModel(this, db);
      ui->username_line->clear();
      ui->password_line->clear();
      ui->stackedWidget->setCurrentIndex(ADMIN);
      ui->customer_tableView->setModel(cTableModel);
      ui->customer_tableView->resizeColumnToContents(CustomerTableModel::NAME);
      ui->customer_tableView->hideColumn(CustomerTableModel::KEY);
      ui->customer_tableView->hideColumn(CustomerTableModel::INTEREST);
      ui->customer_tableView->hideColumn(CustomerTableModel::ID);
    }
    else
    {
      qDebug() <<"UNACCEPTABLE!!!!";
    }
  }
  else
  {
    qDebug() << "EMPTY!!!";
  }
}

void MainWindow::on_login_buttonBox_rejected()
{
    ui->username_line->clear();
    ui->password_line->clear();
    ui->stackedWidget->setCurrentIndex(0 /*make this WELCOME later*/);
}

void MainWindow::on_customer_tableView_activated(const QModelIndex &index)
{
  cTableModel = new CustomerTableModel(this, db);
  ui->customer_tableView->setModel(cTableModel);
}

void MainWindow::on_password_line_returnPressed()
{
  ui->login_buttonBox->accepted();
}

void MainWindow::on_key_customers_checkBox_toggled(bool checked)
{
    if(checked)
    {
      cTableModel->IsKeyToggle();
    }
    else
    {
      cTableModel->setFilter("");
    }
}
