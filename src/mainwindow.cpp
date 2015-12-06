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

void MainWindow::on_login_buttonBox_accepted()
{
  if(!ui->username_line->text().isEmpty() && !ui->password_line->text().isEmpty())
  {
    if(db->Authenticate(ui->username_line->text(), ui->password_line->text()))
    {
      cTableModel = new CustomerTableModel(this, db);
      tTableModel = new TestimonialTableModel(this, db);
      ui->customer_tableView->setModel(cTableModel);
      ui->testimonial_tableView->setModel(tTableModel);
      InitTestimonialTableView();
      ui->username_line->clear();
      ui->password_line->clear();
      ui->stacked_pages->setCurrentIndex(ADMINISTRATOR);
      ui->customer_tableView->setModel(cTableModel);
      ui->customer_tableView->hideColumn(CustomerTableModel::ID);
      ui->customer_tableView->resizeColumnToContents(CustomerTableModel::NAME);
      ui->customer_tableView->resizeColumnToContents(CustomerTableModel::INTEREST);
      ui->customer_tableView->resizeColumnToContents(CustomerTableModel::KEY);
//      ui->customer_tableView->resizeColumnsToContents();
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
  ui->stacked_pages->setCurrentIndex(0 /*make this WELCOME later*/);
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

void MainWindow::on_customer_key_customers_checkBox_toggled(bool checked)
{
  enum Interest
  {
    ALL,
    NOT,
    SOMEWHAT,
    VERY
  };
  if(checked)
  {
    switch(ui->customer_interest_comboBox->currentIndex())
    {
    case ALL:
      cTableModel->setFilter("key = 1");
      break;
    case NOT:
      cTableModel->setFilter("key = 1 and interest = 0");
      break;
    case SOMEWHAT:
      cTableModel->setFilter("key = 1 and interest = 1");
      break;
    case VERY:
      cTableModel->setFilter("key = 1 and interest = 2");
      break;
    default:
      cTableModel->setFilter("key = 1");
    }
  }
  else
  {
    switch(ui->customer_interest_comboBox->currentIndex())
    {
    case ALL:
      cTableModel->setFilter("");
      break;
    case NOT:
      cTableModel->setFilter("interest = 0");
      break;
    case SOMEWHAT:
      cTableModel->setFilter("interest = 1");
      break;
    case VERY:
      cTableModel->setFilter("interest = 2");
      break;
    default:
      cTableModel->setFilter("");
    }
  }
}

void MainWindow::on_administrator_toolBox_currentChanged(int index)
{
  enum toolboxPage
  {
    CUSTOMERS,
    TESTIMONIALS
  };
  switch(index)
  {
  case CUSTOMERS:
    cTableModel->select();
    break;
  case TESTIMONIALS:
    InitTestimonialTableView();
    tTableModel->select();
  }
}

void MainWindow::on_testimonial_add_button_clicked()
{
  AddTestimonialPopup *p;
  //instantiate popup window
  p = new AddTestimonialPopup(0, db, tTableModel);

  //Disable other windows
  p->setWindowModality(Qt::ApplicationModal);
  //display popup
  p->show();
}

void MainWindow::InitTestimonialTableView()
{
  ui->testimonial_tableView->setEditTriggers(QTableView::NoEditTriggers);
  ui->testimonial_tableView->setAlternatingRowColors(true);
  ui->testimonial_tableView->verticalHeader()->setVisible(false);
  ui->testimonial_tableView->hideColumn(TestimonialTableModel::ID);
  ui->testimonial_tableView->hideColumn(TestimonialTableModel::IMAGE);
  ui->testimonial_tableView->hideColumn(TestimonialTableModel::APPROVED);
  ui->testimonial_tableView->setWordWrap(true);
  ui->testimonial_tableView->setSortingEnabled(true);
  ui->testimonial_tableView->horizontalHeader()->setStretchLastSection(true);
  ui->testimonial_tableView->resizeRowsToContents();
}

void MainWindow::on_testimonial_remove_button_clicked()
{
  if(tTableModel->removeRow(ui->testimonial_tableView->currentIndex().row()))
  {
    tTableModel->submitAll();
    tTableModel->select();
    qDebug() << "TESTIMONIAL REMOVED!";
  }
  else
  {
    qDebug() << "SELECT A ROW YA DINGUS!!";
  }

}

void MainWindow::on_testimonial_approve_button_clicked()
{
  int row = ui->testimonial_tableView->currentIndex().row();
  if(row > -1)
  {
    if(!tTableModel->record(row).field("approved").value().toInt())
    {
      QString name = tTableModel->record(row).field("name").value().toString();
      if(db->SetQuery("update testimonials set approved = 1 where name =\"" + name + "\";"))
      {
        if(db->Exec())
        {
          tTableModel->select();
          qDebug() << "TESTIMONIAL APPROVED!";
        }
        else
        {
          qDebug() << "INVALID QUERY!";
        }
      }
      else
      {
        qDebug() << "INVALID QUERY!";
      }
    }
    else
    {
      qDebug() << "TESTIMONIAL ALREADY APPROVED!";
    }
  }
  else
  {
    qDebug() << "SELECT A ROW YA DINGUS!!";
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

void MainWindow::on_customer_remove_button_clicked()
{
  if(cTableModel->removeRow(ui->customer_tableView->currentIndex().row()))
  {
    cTableModel->submitAll();
    cTableModel->select();
    qDebug() << "CUSTOMER REMOVED!";
  }
  else
  {
    qDebug() << "SELECT A ROW YA DINGUS!!";
  }
}


void MainWindow::on_customer_interest_comboBox_currentIndexChanged(int index)
{
  enum Interest
  {
    ALL,
    NOT,
    SOMEWHAT,
    VERY
  };

  if(!ui->customer_key_customers_checkBox->isChecked())
  {
    switch(index)
    {
    case ALL:
      cTableModel->setFilter("");
      break;
    case NOT:
      cTableModel->setFilter("interest = 0");
      break;
    case SOMEWHAT:
      cTableModel->setFilter("interest = 1");
      break;
    case VERY:
      cTableModel->setFilter("interest = 2");
      break;
    }
  }
  else
  {
    switch(index)
    {
    case ALL:
      cTableModel->setFilter("key = 1");
      break;
    case NOT:
      cTableModel->setFilter("key = 1 and interest = 0");
      break;
    case SOMEWHAT:
      cTableModel->setFilter("key = 1 and interest = 1");
      break;
    case VERY:
      cTableModel->setFilter("key = 1 and interest = 2");
      break;
    }
  }
  cTableModel->select();
}

void MainWindow::on_customer_purchase_button_clicked()
{
  int row = ui->customer_tableView->currentIndex().row();
  if(row != -1)
  {
    int id = cTableModel->record(row).field("id").value().toInt();
    pTableModel = new PurchasesTableModel(this, db, id);
    ViewPurchasesPopup *p;
    p = new ViewPurchasesPopup(0, db, pTableModel);
    p->setWindowModality(Qt::ApplicationModal);
    p->show();
  }
  else
  {
    qDebug() << "SELECT A ROW YA DINGUS!!";
  }
}

void MainWindow::on_customer_submit_changes_button_clicked()
{
  if(cTableModel->submitAll())
  {
    qDebug() << "CHANGES APPLIED TO CUSTOMER TABLE";
  }
  else
  {
    qDebug() << "CHANGES NOT APPLIED TO CUSTOMER TABLE";
  }

}
