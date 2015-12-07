#include "mainwindow.h"
#include "ui_MainWindow.h"
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  db = new Database("./data/data.db", "QSQLITE");
  this->setFixedSize(800,600);

  // setup the background
  background = new QLabel(this);
  QMovie *movie = new QMovie(":/images/slowmatrix.gif");
  setBackground(movie,45);

  // setups the rest of the ui on top of the background
  ui->setupUi(this);
  testimonials = NULL;
  UpdateTestimonialList();
  LoadProductList();


  // TEMP sets the default page to login screen
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
      ui->username_line->setCursorPosition(0);
    }
    else if(db->AuthenticateUser(ui->username_line->text(), ui->password_line->text()))
    {
      SetActiveUser(db->GetUserIdByName(ui->username_line->text()));
      ui->stacked_pages->setCurrentIndex(CUSTOMER);
      ui->toolBox->setCurrentIndex(0);
      ui->username_line->clear();
      ui->password_line->clear();
      ui->username_line->setCursorPosition(0);
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
  ui->username_line->setCursorPosition(0);
  ui->stacked_pages->setCurrentIndex(INTRO);
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
          testimonials = db->GetApprovedTestimonials();
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

    if(db->AddUser(db->GetCustomerIdByName(ui->company_line->text()), ui->username_line_2->text(), ui->password_line_2->text()))
    {
      qDebug() << ui->username_line_2->text() << " added the the users table.\n";
    }
  }



}

void MainWindow::setBackground(QMovie *movie, int speed)
{
  // loads the background movie into a label
  background->resize(this->size());
  background->setMovie(movie);

  movie->setSpeed(speed);
  movie->start();
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


void MainWindow::Register_ClearForms()
{
  ui->username_line_2->clear();
  ui->password_line_2->clear();
  ui->address_line->clear();
  ui->terms_box->setChecked(0);
  ui->interest_box->setCurrentIndex(0);
  ui->company_line->clear();
}

void MainWindow::SetTestimonialView(int index)
{
  if(index >= 0 && index < testimonials->size())
  {
    QPixmap image( "images/" + testimonials->at(index).field("image").value().toString() );
    image = image.scaled(ui->customer_testimonials_picture->width(), ui->customer_testimonials_picture->height(), Qt::KeepAspectRatio);

    ui->customer_testimonials_text->setText( testimonials->at(index).field("testimonial").value().toString() );
    ui->customer_testimonials_picture->setPixmap(image);
    //    qDebug() << "TESTIMONIAL TEXT: " << testimonials->at(position).field("testimonial").value().toString();
    //    qDebug() << "TESTIMONIAL IMAGE PATH: " << testimonials->at(position).field("image").value().toString();
  }
  else
  {
    qDebug() << "***** INVALID TESTIMONIAL INDEX!!! ******";
  }
}

void MainWindow::UpdateTestimonialList()
{
  if(testimonials != NULL){
    delete testimonials;
  }
  testimonials = db->GetApprovedTestimonials();
  qDebug() << "TESTIMONIALS LIST SIZE: " << testimonials->size();
  ui->customer_testimonial_slider->setMinimum(0);
  ui->customer_testimonial_slider->setMaximum(testimonials->size()-1);
  SetTestimonialView(ui->customer_testimonial_slider->value());
}

void MainWindow::LoadProductList()
{
  ProductInfo temp;
  temp.productName = "Tiger© Threat Protection";
  temp.html        = "qrc:/html/TIGERThreat.html";
  ProductInfoList.push_back(temp);
  temp.productName = "Tiger© Insider Threat";
  temp.html        = "qrc:/html/TIGERInsider.html";
  ProductInfoList.push_back(temp);
  temp.productName = "Tiger© Analytics";
  temp.html        = "qrc:/html/TIGERAnalytics.html";
  ProductInfoList.push_back(temp);
  temp.productName = "Tiger© Memory Integrity";
  temp.html        = "qrc:/html/TIGERMemoryIntegrity.html";
  ProductInfoList.push_back(temp);
  temp.productName = "Tiger© Email Security";
  temp.html        = "qrc:/html/TIGEREmail.html";
  ProductInfoList.push_back(temp);

  ui->customer_products_slider->setMinimum(0);
  ui->customer_products_slider->setMaximum(ProductInfoList.size()-1);
  ui->customer_products_title->setText(ProductInfoList.at(ui->customer_products_slider->value()).productName);
  ui->customer_products_webview->setUrl(ProductInfoList.at(ui->customer_products_slider->value()).html);
}

void MainWindow::SetActiveUser(QString id)
{
  activeUserId = id;
}

void MainWindow::on_finished_intro()
{
  QPropertyAnimation *titlein = new QPropertyAnimation(ui->welcomeTitle, "geometry");
  titlein->setDuration(200);
  ui->welcomeTitle->show();
  titlein->setStartValue(QRect(262,-120,500,120));
  titlein->setEndValue(QRect(262,57,500,120));
  titlein->start();
  ui->welcomeBtn->setEnabled(true);
}


void MainWindow::on_welcomeBtn_clicked()
{}

void MainWindow::on_customer_remove_button_clicked()
{
  int row =ui->customer_tableView->currentIndex().row();

  if(cTableModel->removeRow(row))
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

void MainWindow::on_customer_testimonial_slider_sliderMoved(int position)
{
  SetTestimonialView(position);
}

void MainWindow::on_customer_testimonial_slider_valueChanged(int value)
{
  SetTestimonialView(value);
}

void MainWindow::on_toolBox_currentChanged(int index)
{
  switch(index){
  case CUST_PRODUCTS : break;
  case CUST_TESTIMONIALS : UpdateTestimonialList();
    break;
  case CUST_PURCHASE : break;
  default : break;
  }
}

void MainWindow::on_customer_products_slider_valueChanged(int value)
{
  ui->customer_products_title->setText(ProductInfoList.at(value).productName);
  ui->customer_products_webview->setUrl(ProductInfoList.at(value).html);
}

void MainWindow::on_GeneralInfoButton_clicked()
{
  ui->InformationSpace->setSource(QUrl("qrc:/html/INFOGeneral.html"));
}

void MainWindow::on_ConceptOfOperations_clicked()
{
  ui->InformationSpace->setSource(QUrl("qrc:/html/INFOCop.html"));
}

void MainWindow::on_SupportedPlattaforms_clicked()
{
  ui->InformationSpace->setSource(QUrl("qrc:/html/INFOPlatforms.html"));
  qDebug() << ui->InformationSpace->source();
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
  Register_ClearForms();
  ui->stacked_pages->setCurrentIndex(LOGIN);
}

void MainWindow::on_register_cancel_button_clicked()
{
  Register_ClearForms();
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

void MainWindow::on_customer_purchase_purchaseButton_clicked()
{
  //Go to page that says thanks for your purchase?
  if(ui->customer_purchase_product_checkBox->isChecked())
  {
    db->Purchase(activeUserId, "1");
    ui->customer_purchase_product_checkBox->setChecked(0);
  }
  if(ui->customer_purchase_product_checkBox_2->isChecked())
  {
    db->Purchase(activeUserId, "2");
    ui->customer_purchase_product_checkBox_2->setChecked(0);
  }
  if(ui->customer_purchase_product_checkBox_3->isChecked())
  {
    db->Purchase(activeUserId, "3");
    ui->customer_purchase_product_checkBox_3->setChecked(0);
  }
  if(ui->customer_purchase_product_checkBox_4->isChecked())
  {
    db->Purchase(activeUserId, "4");
    ui->customer_purchase_product_checkBox_4->setChecked(0);
  }
  if(ui->customer_purchase_product_checkBox_5->isChecked())
  {
    db->Purchase(activeUserId, "5");
    ui->customer_purchase_product_checkBox_5->setChecked(0);
  }

}

void MainWindow::on_pushButton_2_clicked()
{
  ui->toolBox->setCurrentIndex(0);
}

void MainWindow::on_customer_logout_button_clicked()
{
  ui->stacked_pages->setCurrentIndex(LOGIN);
}

void MainWindow::on_add_testimonial_buttonBox_accepted()
{
  QString name = db->GetCustomerNameById(activeUserId);

  if(!ui->add_testimonial_text->toPlainText().isEmpty())
  {
    if(db->AddTestimonial(name, ui->add_testimonial_text->toPlainText()))
    {
      qDebug() << "TESTIMONIAL ADDED";
      ui->toolBox->setCurrentIndex(0);
    }
    else
    {
      qDebug() << "USERS GET ONE TESTIMONIAL. ONLY ONE!";
    }
  }
  else
  {
    qDebug() << "TESTIMONIAL IS EMPTY!";
  }
  ui->add_testimonial_text->clear();
}

void MainWindow::on_add_testimonial_text_textChanged()
{
  if(ui->add_testimonial_text->toPlainText().length() >= 500)
  {
    ui->add_testimonial_text->textCursor().deletePreviousChar();
  }
}
