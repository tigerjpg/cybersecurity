#include "mainwindow.h"
#include "ui_MainWindow.h"
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  db = new Database("./data/data.db", "QSQLITE");
  this->setFixedSize(800,600);

  ui->stacked_pages->setCurrentIndex(LOGIN);
  ui->stacked_pages->setCurrentIndex(REGISTER);
  ui->register_okay_button->setEnabled(false);



}

MainWindow::~MainWindow()
{
  delete ui;
}

bool MainWindow::RegistrationCompleted()
{
  if(!ui->username_label_2->text().isEmpty() &&
     !ui->password_label_2->text().isEmpty() &&
     !ui->company_line->text().isEmpty() &&
     !ui->address_line->text().isEmpty() &&
     ui->interest_box->currentIndex() > 0 &&
     ui->terms_box->isChecked())
  {
    qDebug() << "registration complete\n";
    return true;
  }
  else
  {
    qDebug() << "registration incomplete\n";
    ui->register_okay_button->setEnabled(false);
    return false;
  }
}

void MainWindow::Register()
{
  if(db->AddCustomer(ui->company_line->text(), ui->address_line->text(),
                  QString::number(ui->interest_box->currentIndex()-1), "false"))
  {
    qDebug() << ui->company_line->text() << " added to the customer table.\n";
  }
}


void MainWindow::WelcomeAnimation()
{
  ui->welcomeBtn->setEnabled(false);
  QPropertyAnimation *tigershield = new QPropertyAnimation(ui->welcomeBtn, "geometry");
  connect(tigershield, SIGNAL(finished()), this, SLOT(on_finished_intro() ));
  tigershield->setDuration(1500);
  tigershield->setStartValue(QRect(-25, -216, 1200, 1200));
  tigershield->setEndValue(QRect((1024/2)-178, (768/2)-200, 400, 400));
  tigershield->start();
}

void MainWindow::on_finished_intro()
{
  QPropertyAnimation *titlein = new QPropertyAnimation(ui->welcomeTitle, "geometry");
//  connect(titlein, SIGNAL(finished()), this, SLOT(on_finished_intro() ));
  titlein->setDuration(200);
  ui->welcomeTitle->show();
  titlein->setStartValue(QRect(262,-120,500,120));
  titlein->setEndValue(QRect(262,57,500,120));
  titlein->start();
  ui->welcomeBtn->setEnabled(true);
}


void MainWindow::on_welcomeBtn_clicked()
{
}

bool MainWindow::defaultCustomerView()
{
  sql_table_model->setTable("customers");
  return sql_table_model->select();
}

bool MainWindow::keyCustomerView()
{
  sql_table_model->setTable("customers");
  sql_table_model->setFilter("key = \"1\"");
  return sql_table_model->select();
}

bool MainWindow::interestCustomerView(int i)
{
  QString interest = QString::number(i);
  sql_table_model->setTable("customers");
  sql_table_model->setFilter("interest = \"" + interest + "\";");
  return sql_table_model->select();
}

bool MainWindow::interestAndKeyCustomerView(int i)
{
  QString interest = QString::number(i);
  sql_table_model->setTable("customers");
  sql_table_model->setFilter("key = \"1\" and interest = \"" + interest + "\";");
  return sql_table_model->select();
}


void MainWindow::on_username_line_2_editingFinished()
{
    if(RegistrationCompleted())
      ui->register_okay_button->setEnabled(true);
}

void MainWindow::on_password_line_2_editingFinished()
{
  if(RegistrationCompleted())
    ui->register_okay_button->setEnabled(true);
}

void MainWindow::on_company_line_editingFinished()
{
  if(RegistrationCompleted())
    ui->register_okay_button->setEnabled(true);
}

void MainWindow::on_address_line_editingFinished()
{
  if(RegistrationCompleted())
    ui->register_okay_button->setEnabled(true);
}

void MainWindow::on_interest_box_currentIndexChanged(int index)
{
  if(RegistrationCompleted())
    ui->register_okay_button->setEnabled(true);
}

void MainWindow::on_terms_box_toggled(bool checked)
{
  if(RegistrationCompleted())
    ui->register_okay_button->setEnabled(true);
}

void MainWindow::on_register_okay_button_clicked()
{
  Register();
  ui->stacked_pages->setCurrentIndex(LOGIN);
}
