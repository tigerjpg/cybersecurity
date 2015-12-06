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



}

MainWindow::~MainWindow()
{
  delete ui;
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


void MainWindow::on_checkBox_stateChanged(int arg1)
{
  switch(arg1)
  {
  case 0:
    switch(ui->interest_level_box->currentIndex())
    {
    case 0:
      defaultCustomerView();
      break;
    case 1:
    case 2:
    case 3:
      interestCustomerView(ui->interest_level_box->currentIndex() - 1);
    }
    break;
  case 2:
    switch(ui->interest_level_box->currentIndex())
    {
    case 0:
      keyCustomerView();
      break;
    case 1:
    case 2:
    case 3:
      interestAndKeyCustomerView(ui->interest_level_box->currentIndex() - 1);
    }
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
  if(ui->checkBox->isChecked())
  {
    switch(index)
    {
    case 0:
      keyCustomerView();
      break;
    case 1:
    case 2:
    case 3:
      interestAndKeyCustomerView(index - 1);
    }
  }
  else
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
}

void MainWindow::on_testimonial_slider_valueChanged(int value)
{
  ui->testimonial_text->setText(db->getTestimonialAtIndex(value));
  ui->testimonial_image->setPixmap(QPixmap::fromImage(QImage(":/images/" + db->getImageAtIndex(value)).scaled(ui->testimonial_image->size())));
}

void MainWindow::on_GeneralInfoButton_clicked()
{
    QString generalInfo = "T.I.G.E.R Inc\n\n"
                          "Address: 3 Cheetah Avenue, Irvine, C.A 92614\n"
                          "Phone Number: 949-420-6969\n"
                          "Email Address: TigerInc@Tiger.cjpg";
    //ui->information_text->setText(generalInfo);

    QTextBrowser :: wordWrapMode();
   QTextBrowser :: setReadOnly(generalInfo);
}

void MainWindow::on_MissioButton_clicked()
{
    QString missionStatement = "Our Mission:\n\n"
                               "This company was created by Ernest L. Cheetahiser in January, 1991.\n"
                               "The reason to create this company was to provide the public with solutions\n"
                               "to new cyber security threats.\n"
                               "We want to make the business world safe and reliable in order to have a more\n"
                               "stable market and economy.";
    //ui->information_text->setText(missionStatement);

     QTextBrowser :: wordWrapMode();
    QTextBrowser :: setReadOnly(missionStatement);



}

void MainWindow::on_WhatWeDo_clicked()
{
    QString whatWeDo = "What We Do: \n\n"
                       "We create all kinds of solutions to cyberthreats. We create products that prevent data leaks from within and outside the company. We also create environments that fight cyber attackers and provide ways to know the source of the issue so future attacks can be prevented. The company has in it's mind that time is precious, that is why we provide the fastest and most reliable technical and costumer service in the market. We care and protect our costumers better than ourselves.";
    //whatWeDo.

    QTextBrowser :: wordWrapMode();
   QTextBrowser :: setReadOnly(whatWeDo);

}

void MainWindow::on_HowWeDo_clicked()
{
    QString howWeDo = "How We do it\n\n"
                      "We use cutting edge technology for our systems as well as the most efficient software. Our development team makes sure that the data we manage is always safe and our software not interfering with the traffic. Because we care about our clients, we have meetings with company employees to find ways to improve our services and products.";

    QTextBrowser :: wordWrapMode();
   QTextBrowser :: setReadOnly(howWeDo);
}
