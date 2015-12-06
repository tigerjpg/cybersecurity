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
    if(db->AuthenticateAdmin(ui->username_line->text(), ui->password_line->text()))
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
      InitCustomerTableView();
    }
    else if(db->AuthenticateUser(ui->username_line->text(), ui->password_line->text()))
    {
      ui->stacked_pages->setCurrentIndex(CUSTOMER);
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
    NEVER,
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
    case NEVER:
      cTableModel->setFilter("key = 1 and interest = 0");
      break;
    case NOT:
      cTableModel->setFilter("key = 1 and interest = 1");
      break;
    case SOMEWHAT:
      cTableModel->setFilter("key = 1 and interest = 2");
      break;
    case VERY:
      cTableModel->setFilter("key = 1 and interest = 3");
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
    case NEVER:
      cTableModel->setFilter("interest = 0");
      break;
    case NOT:
      cTableModel->setFilter("interest = 1");
      break;
    case SOMEWHAT:
      cTableModel->setFilter("interest = 2");
      break;
    case VERY:
      cTableModel->setFilter("interest = 3");
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

/*!
 * \brief MainWindow::on_testimonial_add_button_clicked
 * Add a testimonial. Creates a popup window.
 */
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

/*!
 * \brief MainWindow::InitTestimonialTableView
 * Initialize the Testimonial TableView
 */
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

/*!
 * \brief MainWindow::InitCustomerTableView
 * Initialize the customer tableView
 */
void MainWindow::InitCustomerTableView()
{
  ui->customer_tableView->hideColumn(CustomerTableModel::ID);
  ui->customer_tableView->resizeColumnToContents(CustomerTableModel::INTEREST);
  ui->customer_tableView->resizeColumnToContents(CustomerTableModel::SENT);
  ui->customer_tableView->horizontalHeader()->setStretchLastSection(true);
}

/*!
 * \brief MainWindow::on_testimonial_remove_button_clicked
 * Remove a testimonial
 */
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

/*!
 * \brief MainWindow::on_testimonial_approve_button_clicked
 * Approve a testimonial
 */
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
    ui->register_okay_button->setEnabled(true);
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
                     QString::number(ui->interest_box->currentIndex()-1), "false", "0"))
  {
    qDebug() << ui->company_line->text() << " added to the customer table.\n";

    if(db->AddUser(db->GetCustomerIdByName(ui->company_line->text()), ui->username_line_2->text(), ui->password_line_2->text(), "false"))
    {
      qDebug() << ui->username_line_2->text() << " added the the users table.\n";
    }
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


/*!
 * \brief MainWindow::on_customer_interest_comboBox_currentIndexChanged
 * View only customers of a certain interest level.
 * \param index
 */
void MainWindow::on_customer_interest_comboBox_currentIndexChanged(int index)
{
  enum Interest
  {
    ALL,
    NEVER,
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
    case NEVER:
      cTableModel->setFilter("interest = 0");
      break;
    case NOT:
      cTableModel->setFilter("interest = 1");
      break;
    case SOMEWHAT:
      cTableModel->setFilter("interest = 2");
      break;
    case VERY:
      cTableModel->setFilter("interest = 3");
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
    case NEVER:
      cTableModel->setFilter("key = 1 and interest = 0");
      break;
    case NOT:
      cTableModel->setFilter("key = 1 and interest = 1");
      break;
    case SOMEWHAT:
      cTableModel->setFilter("key = 1 and interest = 2");
      break;
    case VERY:
      cTableModel->setFilter("key = 1 and interest = 3");
      break;
    }
  }
  cTableModel->select();
}

/*!
 * \brief MainWindow::on_customer_purchase_button_clicked
 * Create a popup window with a table with the purchases
 * of the specific customer you have selected.
 */
void MainWindow::on_customer_purchase_button_clicked()
{
  int row = ui->customer_tableView->currentIndex().row();
  if(row != -1)
  {
    int id = cTableModel->record(row).field("id").value().toInt();
    qDebug() << id;
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

/*!
 * \brief MainWindow::on_customer_submit_changes_button_clicked
 * Finalize changes made to the customer table
 */
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

/*!
 * \brief MainWindow::on_customer_add_pushButton_clicked
 * Creates a popup window with a form to add Customers
 */
void MainWindow::on_customer_add_pushButton_clicked()
{
  AddCustomerPopup *p = new AddCustomerPopup(0, db, cTableModel);
  p->setWindowModality(Qt::ApplicationModal);
  p->show();
}

/*!
 * \brief MainWindow::on_customer_send_pamphlet_button_clicked
 * Alter customers table "sent" value
 */
void MainWindow::on_customer_send_pamphlet_button_clicked()
{
  //Check if row is selected
  int row = ui->customer_tableView->currentIndex().row();
  if(row > -1)
  {
    //If customer has not been sent a pamphlet (sent == 0)
    if(!cTableModel->record(row).field("sent").value().toInt())
    {
      QString name = cTableModel->record(row).field("name").value().toString();
      if(db->SetQuery("update customers set sent = 1 where name = \"" + name + "\";"))
      {
        if(db->Exec())
        {
          cTableModel->select();
          qDebug() << "CUSTOMER HAS BEEN SENT A PAMPHLET! HOO-AHH!";
        }
      }
      else
      {
        qDebug() << "INVALID QUERY!";
      }
    }
    else
    {
      qDebug() << "CUSTOMER HAS ALREADY BEEN SENT A PAMPHLET! GOSH";
    }
  }
  else
  {
    qDebug() << "SELECT A ROW YA DINGUS!";
  }
}

void MainWindow::on_GeneralInfoButton_clicked()
{
  QString generalInfo = "T.I.G.E.R Inc\n\n"
                        "Address: 3 Cheetah Avenue, Irvine, C.A 92614\n"
                        "Phone Number: 949-420-6969\n"
                        "Email Address: TigerInc@Tiger.cjpg\n\n";
  QString missionStatement = "Our Mission:\n\n"
                             "This company was created by Ernest L. Cheetahiser in January, 1991."
                             "The reason to create this company was to provide the public with solutions "
                             "to new cyber security threats. "
                             "We want to make the business world safe and reliable in order to have a more "
                             "stable market and economy.\n\n";

  QString whatWeDo = "What We Do: \n\n"
                     "We create all kinds of solutions to cyberthreats."
                     " We create products that prevent data leaks from within and outside the company. "
                     "We also create environments that fight cyber attackers and provide ways to know the source "
                     "of the issue so future attacks can be prevented. The company has in it's mind that time"
                     " is precious, that is why we provide the fastest and most reliable technical and costumer service in the market. "
                     "We care and protect our costumers better than ourselves\n\n.";

  QString howWeDo = "How We do it:\n\n"
                    "We use cutting edge technology for our systems as well as the most efficient software. "
                    "Our development team makes sure that the data we manage is always safe and our software "
                    "not interfering with the traffic. Because we care about our clients, we have meetings with company "
                    "employees to find ways to improve our services and products.\n\n";



  //ui->information_text->setText(generalInfo);

  ui->InformationSpace->setText(generalInfo + missionStatement + whatWeDo + howWeDo);

}

void MainWindow::on_ConceptOfOperations_clicked()
{
  QString conceptOfOperations = "Concept Of Operations\n\n"
                                "TIGER products are delivered within 2 business day of purchase. TIGER's Technitians come to the"
                                "costumer, take control of all the hardware necessary to install the purchased products. Upon installation, the"
                                "company will provide the services promised in time matter. The company will run a test to see if the software"
                                "is working as intended. In case of a fail in the test, TIGER will fix the issue without any additional cost, just"
                                "as specified in the policy. TIGER installs the systems within 48 hours. It requires that the costumer provides all"
                                " the current security details of the server. Nothing will be changed, instead, more security features will be"
                                "install on top of the curent. Tiger keeps a data base of employees and contacts them every quarter to see if the systems"
                                "are up to date, or to discuss contract clauses.\n\n";

  ui->InformationSpace->setText(conceptOfOperations);
}

void MainWindow::on_SupportedPlattaforms_clicked()
{
  QString plattaforms =   "Supported Plattaforms\n\n"
                          "Ubuntu\n"
                          "Debian\n"
                          "Mint\n"
                          "Fedora\n"
                          "CentOs/Red Hat Enterprise Linux\n"
                          "openSUSE/SUSE Linux Enterprise\n"
                          "Mageia/Mandriva\n"
                          "Arch Linux\n"
                          "Slackware Linux\n\n"

                          "Others:\n\n"

                          "none\n\n"

                          "Hardware (Minimum):\n\n"

                          "Intel® Xeon®\n"
                          "500 TB of Memory";

  ui->InformationSpace->setText(plattaforms);
}

void MainWindow::on_RegisterButton_clicked()
{
  ui->stacked_pages->setCurrentIndex(REGISTER);
  ui->register_okay_button->setEnabled(false);
  ui->username_line_2->setValidator(new QRegExpValidator(QRegExp("[\\w]*")));
  ui->company_line->setValidator(new QRegExpValidator(QRegExp("[\\w\\s]*")));
}

void MainWindow::on_username_line_2_editingFinished()
{
  RegistrationCompleted();
}

void MainWindow::on_password_line_2_editingFinished()
{
  RegistrationCompleted();
}

void MainWindow::on_company_line_editingFinished()
{
  RegistrationCompleted();
}

void MainWindow::on_address_line_editingFinished()
{
  RegistrationCompleted();
}

void MainWindow::on_interest_box_currentIndexChanged(int index)
{
  RegistrationCompleted();
}

void MainWindow::on_terms_box_toggled(bool checked)
{
  RegistrationCompleted();
}

void MainWindow::on_register_okay_button_clicked()
{
  Register();
  ui->username_line_2->clear();
  ui->password_line_2->clear();
  ui->address_line->clear();
  ui->terms_box->setChecked(0);
  ui->interest_box->clear();
  ui->company_line->clear();
  ui->stacked_pages->setCurrentIndex(LOGIN);
}

void MainWindow::on_register_cancel_button_clicked()
{
  // Maybe forms need to be cleared.
  ui->stacked_pages->setCurrentIndex(LOGIN);
}

void MainWindow::on_OKgoBackLogIn_clicked()
{
  ui->stacked_pages->setCurrentIndex(LOGIN);
}

void MainWindow::on_InformationButton_clicked()
{
  ui->stacked_pages->setCurrentIndex(INFORMATION);
}

void MainWindow::on_admin_logout_button_clicked()
{
  ui->stacked_pages->setCurrentIndex(LOGIN);
//  delete cTableModel;
//  delete tTableModel;
//  delete pTableModel;
}
