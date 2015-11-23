#include "mainwindow.h"
#include "ui_MainWindow.h"
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  db = new Database("./data/data.db", "QSQLITE");

  // load all the backgrounds into the background vectors
  mainBackground.append(QPixmap(":/images/tiger.jpg"));
  mainBackground.append(QPixmap(":/images/tiger2.jpg"));
  mainBackground.append(QPixmap(":/images/tiger3.jpg"));
  mainBackground.append(QPixmap(":/images/tiger4.jpg"));
  mainBackground.append(QPixmap(":/images/tiger5.jpg"));

  // set the default view
  on_page1_clicked();

  // load the images into buttons
  qDebug() << "Setting button images: " << ui->pushButton->SetButtonImage(":/images/tiger.png", ":/images/tiger-hover.png", ":/images/tiger-click.png");
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::TigerButton()
{
  ui->lcdNumber->display(ui->lcdNumber->intValue() + 1);
}

void MainWindow::LaserOn()
{
  QPixmap background(":/images/tiger2.jpg");
  QPalette backgroundBrush;
  backgroundBrush.setBrush(QPalette::Background, background);
  this->setPalette(backgroundBrush);
}

void MainWindow::LaserOff()
{
  QPixmap background(":/images/tiger.jpg");
  QPalette backgroundBrush;
  backgroundBrush.setBrush(QPalette::Background, background);
  this->setPalette(backgroundBrush);
}

void MainWindow::changeBackground(int index)
{
  // ensure that the index is always in range
  index %= mainBackground.size();

  // set the window size and paint the background
  this->setFixedSize(QSize( mainBackground[index].width(), mainBackground[index].height() ));
  QPalette backgroundBrush;
  backgroundBrush.setBrush(QPalette::Background, mainBackground[index]);
  this->setPalette(backgroundBrush);
}

void MainWindow::on_page0_clicked()
{
  ui->stackedWidget->setCurrentIndex(0);
  changeBackground(0);
}

void MainWindow::on_page1_clicked()
{
  ui->stackedWidget->setCurrentIndex(1);
  changeBackground(1);
}

void MainWindow::on_page2_clicked()
{
  ui->stackedWidget->setCurrentIndex(2);
  changeBackground(2);
}

void MainWindow::on_page3_clicked()
{
  ui->stackedWidget->setCurrentIndex(4);
  changeBackground(3);
}

void MainWindow::on_page4_clicked()
{
  ui->stackedWidget->setCurrentIndex(5);
  changeBackground(4);
}

void MainWindow::on_ok_button_clicked()
{
  ui->login_error_message->setStyleSheet("QLabel { "
                                         "font: bold; "
                                         "font-size: 18px; "
                                         "text-align: center; "
                                         "color : palette(highlight);  }");
  if(!ui->usernameBox->text().isEmpty() && !ui->passwordBox->text().isEmpty())
  {
    if(db->Authenticate(ui->usernameBox->text(), ui->passwordBox->text()))
    {
      ui->usernameBox->clear();
      ui->passwordBox->clear();
      initializeCustomerView();
    }
    else
    {
      ui->usernameBox->clear();
      ui->passwordBox->clear();
      ui->login_error_message->setText("Invalid login credentials.");
    }
  }
  else
  {
    ui->login_error_message->setText("Please enter your credentials.");
  }
}

void MainWindow::on_clear_button_clicked()
{
  ui->usernameBox->clear();
  ui->passwordBox->clear();
}

void MainWindow::on_passwordBox_returnPressed()
{
  ui->ok_button->click();
}

void MainWindow::on_usernameBox_returnPressed()
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

void MainWindow::on_checkBox_stateChanged(int arg1)
{
  qDebug() << arg1;
  switch(arg1)
  {
  case 0:
    defaultCustomerView();
    break;
  case 2:
    keyCustomerView();
    break;
  }
}

void MainWindow::initializeCustomerView()
{
  ui->stackedWidget->setCurrentIndex(3);
  sql_table_model = new QSqlTableModel(this, *db);
  defaultCustomerView();
  ui->customer_view->setModel(sql_table_model);
  ui->customer_view->hideColumn(0);
  ui->customer_view->hideColumn(3);
  ui->customer_view->hideColumn(4);
  ui->customer_view->resizeColumnsToContents();
  ui->customer_view->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::on_interest_level_box_activated(int index)
{
  switch(index)
  {
  case 0:
    defaultCustomerView();
    break;
  case 1:
  case 2:
  case 3:
    interestCustomerView(index - 1);
  }
}
