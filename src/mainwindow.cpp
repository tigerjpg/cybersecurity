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
  this->setWindowTitle("T.I.G.E.R. Cybersecurity");
  testimonials = NULL;
  UpdateTestimonialList();
  LoadProductList();

  // TEMP sets the default page to login screen
  WelcomeAnimation();
  Welcome();

  // initialize welcome buttons
  ui->help_label->setPixmap(QPixmap(":/images/click4help.png"));
  ui->help_button->SetButtonImage(":/images/tiger.png",
                                  ":/images/tiger-hover.png",
                                  ":/images/tiger-click.png");
  QPixmap logo(":/images/welcome.png");
  logo = logo.scaled(ui->logo_label->width(),ui->logo_label->height(),Qt::KeepAspectRatioByExpanding);
  ui->logo_label->setPixmap(logo);

}
MainWindow::~MainWindow()
{
  delete ui;
}

/*!
 * \brief MainWindow::on_login_buttonBox_accepted
 * Attempt to log a user or admin into the pamphlet/admin window
 */
void MainWindow::on_login_buttonBox_accepted()
{
  if(!ui->username_line->text().isEmpty() && !ui->password_line->text().isEmpty())
  {
    QString username = ui->username_line->text();
    QString password = ui->password_line->text();
    if(db->AuthenticateAdmin(username, password))
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
      ui->administrator_toolBox->setCurrentIndex(0);
    }
    else if(db->AuthenticateUser(username, password))
    {
      QString id = db->GetUserIdByName(username);
      qDebug() << id;
      qDebug() << db->GetCustomerSentStatus(id);
      if(db->GetCustomerSentStatus(id) == "1")
      {
        SetActiveUser(db->GetUserIdByName(ui->username_line->text()));
        ui->stacked_pages->setCurrentIndex(CUSTOMER);
        ui->toolBox->setCurrentIndex(0);
        ui->username_line->clear();
        ui->password_line->clear();
        ui->username_line->setCursorPosition(0);
        ui->customer_products_slider->setSliderPosition(0);
        ui->customer_testimonial_slider->setSliderPosition(1);
        ui->toolBox->setCurrentIndex(0);
        pTableModel = new PurchasesTableModel(0, db, activeUserId.toInt());
        ui->customer_purchase_tableView->setModel(pTableModel);
        InitCustomerPurchaseTableView();
        pTableModel->Initialize();
        pTableModel->select();
      }
      else
      {
        ErrorPopup *p = new ErrorPopup("ACCESS TO PAMPHLET PENDING:\n Please wait until "
                                       "an administrator authorizes your account.");
        p->show();
      }
    }
    else
    {
      ErrorPopup *p = new ErrorPopup("INVALID USERNAME OR PASSWORD.\n Please try again.");
      p->show();
    }
  }
  else
  {
    qDebug() << "EMPTY!!!";
    ErrorPopup *p = new ErrorPopup("FIELDS CANNOT BE BLANK.\n Please try again.");
    p->show();
  }
}

/*!
 * \brief MainWindow::on_login_buttonBox_rejected
 * Clear all fields and return to Welcome page.
 */
void MainWindow::on_login_buttonBox_rejected()
{
  ui->username_line->clear();
  ui->password_line->clear();
  ui->username_line->setCursorPosition(0);
  Welcome();
}

/*!
 * \brief MainWindow::on_customer_tableView_activated
 * Create CustomerTableModel and set customer_tableView to it.
 * \param index
 */
void MainWindow::on_customer_tableView_activated(const QModelIndex &index)
{
  cTableModel = new CustomerTableModel(this, db);
  ui->customer_tableView->setModel(cTableModel);
}

/*!
 * \brief MainWindow::on_password_line_returnPressed
 * Click accept button when return is pressed.
 */
void MainWindow::on_password_line_returnPressed()
{
  ui->login_buttonBox->accepted();
}

/*!
 * \brief MainWindow::on_customer_key_customers_checkBox_toggled
 * check if keyCustomerCheckbox is checked. If it is, set the model
 * Filter accordingly.
 * \param checked the check status of key customer checkBox
 */
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

/*!
 * \brief MainWindow::on_administrator_toolBox_currentChanged
 * Display the correct table when an admin switches the page.
 * \param index
 */
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
    ErrorPopup *p = new ErrorPopup("TESTIMONIAL HAS BEEN REMOVED!");
    p->show();
  }
  else
  {
    ErrorPopup *p = new ErrorPopup("NO ROWS SELECTED.\n Please select a row first.");
    p->show();
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
          ErrorPopup *p = new ErrorPopup("TESTIMONIAL HAS BEEN APPROVED.",
                                         "images/tiger_default.png", "OK!", 0);
          p->show();
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
      ErrorPopup *p = new ErrorPopup("TESTIMONIAL IS ALREADY APPROVED.");
      p->show();
    }
  }
  else
  {
    ErrorPopup *p = new ErrorPopup("NO ROWS SELECTED.\n Please select a row first.");
    p->show();
  }
}

/*!
 * \brief MainWindow::RegistrationCompleted
 * \return true if registration is complete
 */
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

/*!
 * \brief MainWindow::Register
 * Attempt to add a customer to the table of Customers.
 * If successful, add their username and password to the table of Users.
 * \return
 */
bool MainWindow::Register()
{

  if(db->AddCustomer(ui->company_line->text(), ui->address_line->text(),
                     QString::number(ui->interest_box->currentIndex()-1), "false", "0"))
  {
    qDebug() << ui->company_line->text() << " added to the customer table.\n";

    if(db->AddUser(db->GetCustomerIdByName(ui->company_line->text()), ui->username_line_2->text(), ui->password_line_2->text()))
    {
      qDebug() << ui->username_line_2->text() << " added the the users table.\n";
      return true;
    }
  }
  else
  {
    return false;
  }
}

/*!
 * \brief MainWindow::InitializeMaintenance
 * Initialize the maintenance page.
 */
void MainWindow::InitializeMaintenance()
{
  qDebug() << "initializing maintenance paige\n";
  // ui->toolBox->setCurrentIndex(CUST_MAINTENANCE);
  ui->maintenance_textBrowser->setSource(QUrl("qrc:/html/maintenance.html"));
  ui->contact_button->setParent(this);
  if(!ui->contact_button->SetButtonImage("images/tiger-fast.png",
                                         "images/tiger-fast-h.png",
                                         "images/tiger-fast-c.png"))
    qDebug() << "contact button not set\n";
  // ui->contact_button->setEnabled(true);
  ui->contact_button->show();
}

/*!
 * \brief MainWindow::setBackground
 * Set the background to a cool movie.
 * \param movie
 * \param speed
 */
void MainWindow::setBackground(QMovie *movie, int speed)
{
  // loads the background movie into a label
  background->resize(this->size());
  background->setMovie(movie);

  movie->setSpeed(speed);
  movie->start();
}

/*!
* \brief MainWindow::WelcomeAnimation
*  Initiates teh welcome animation
*/
void MainWindow::WelcomeAnimation()
{
  ui->welcomeBtn->SetButtonImage("images/welcome.png","images/welcome-hover.png","images/welcome-click.png");
  ui->welcomeBtn->setEnabled(false);
  ui->welcomeTitle->hide();

  int winW  = this->width();
  int winH  = this->height();
  int start = 1200;
  int end   = 400;

  QPropertyAnimation *tigershield = new QPropertyAnimation(ui->welcomeBtn, "geometry");
  connect(tigershield, SIGNAL(finished()), this, SLOT(on_finished_intro() ));
  tigershield->setDuration(1500);
  tigershield->setStartValue(QRect( 75-((start-winW)/2), -((start-winH)/2), start, start));
  tigershield->setEndValue(QRect((800/2)-175, (600/2)-175, end, end));
  tigershield->start();
}

/*!
* \brief MainWindow::on_finished_intro()
* Once the intro animation is over it brings in the TIGER and
* enables the welcome button
*/
void MainWindow::on_finished_intro()
{
  // Create an animation, with a target object and specified duration
  QPropertyAnimation *titlein = new QPropertyAnimation(ui->welcomeTitle, "geometry");
  titlein->setDuration(200);

  //enable the title off screen and set the end points
  ui->welcomeTitle->show();
  titlein->setStartValue(QRect(200,-120,400,96));
  titlein->setEndValue(QRect(200,25,400,96));
  titlein->start();

  // enable the button once done
  ui->welcomeBtn->setEnabled(true);
}

/*!
* \brief MainWindow::on_welcomeBtn_clicked
* Changes the page to the login page
*/
void MainWindow::on_welcomeBtn_clicked()
{
  Click();
  ui->stacked_pages->setCurrentIndex(LOGIN);
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

/*!
 * \brief MainWindow::SetTestimonialView
 * Set the correct testimonial at each index of the testimonial slider.
 * \param index
 */
void MainWindow::SetTestimonialView(int index)
{
  if(index >= 0 && index < testimonials->size())
  {
    QPixmap image( "images/" + testimonials->at(index).field("image").value().toString() );
    image = image.scaled(ui->customer_testimonials_picture->width(), ui->customer_testimonials_picture->height(), Qt::KeepAspectRatio);

    ui->customer_testimonials_name->setText(testimonials->at(index).field("name").value().toString());
    ui->customer_testimonials_text->setText( testimonials->at(index).field("testimonial").value().toString() );
    ui->customer_testimonials_picture->setPixmap(image);
  }
  else
  {
    qDebug() << "***** INVALID TESTIMONIAL INDEX!!! ******";
  }
}

/*!
 * \brief MainWindow::UpdateTestimonialList
 * Update the list of accepted testimonials.
 */
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

/*!
 * \brief MainWindow::LoadProductList
 * Load the list of products to the products page.
 */
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

/*!
 * \brief MainWindow::SetActiveUser
 * Set activeUserId to the current logged in user.
 * \param id
 */
void MainWindow::SetActiveUser(QString id)
{
  activeUserId = id;
}

/*!
 * \brief MainWindow::ClearAllPurchaseCheckboxes
 * Clear all checkboxes on the customer purchase page.
 */
void MainWindow::ClearAllPurchaseCheckboxes()
{
  ui->customer_purchase_product_checkBox->setChecked(0);
  ui->customer_purchase_product_checkBox_2->setChecked(0);
  ui->customer_purchase_product_checkBox_3->setChecked(0);
  ui->customer_purchase_product_checkBox_4->setChecked(0);
  ui->customer_purchase_product_checkBox_5->setChecked(0);
}

/*!
 * \brief MainWindow::InitCustomerPurchaseTableView
 * Initialize the customer purchase Table
 */
void MainWindow::InitCustomerPurchaseTableView()
{
  ui->customer_purchase_tableView->setAlternatingRowColors(true);
  ui->customer_purchase_tableView->verticalHeader()->hide();
  ui->customer_purchase_tableView->hideColumn(PurchasesTableModel::ID);
  ui->customer_purchase_tableView->hideColumn(PurchasesTableModel::CUSTNAME);
  ui->customer_purchase_tableView->resizeColumnsToContents();
  ui->customer_purchase_tableView->horizontalHeader()->setStretchLastSection(true);
}

/*!
 * \brief MainWindow::on_customer_remove_button_clicked
 * Attempt to remove a customer from the table.
 */
void MainWindow::on_customer_remove_button_clicked()
{
  int row =ui->customer_tableView->currentIndex().row();

  if(cTableModel->removeRow(row))
  {
    cTableModel->submitAll();
    cTableModel->select();
    ErrorPopup *p = new ErrorPopup("CUSTOMER HAS BEEN REMOVED!");
    p->show();
  }
  else
  {
    ErrorPopup *p = new ErrorPopup("NO ROWS SELECTED.\n Please select a row first.");
    p->show();
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
    if(db->HasPurchased(QString::number(id)))
    {
      pTableModel = new PurchasesTableModel(this, db, id);
      ViewPurchasesPopup *p;
      p = new ViewPurchasesPopup(0, db, pTableModel);
      p->setWindowModality(Qt::ApplicationModal);
      p->show();
    }
    else
    {
      ErrorPopup *p = new ErrorPopup("Customer has not purchased anything!",
                                     "images/tiger_default.png", "OK!", 0);
      p->show();
    }
  }
  else
  {
    ErrorPopup *p = new ErrorPopup("NO ROWS SELECTED.\n Please select a row first.");
    p->show();
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
    ErrorPopup *p = new ErrorPopup("Changes have been applied!", "images/tiger_default.png", "OK!", 0);
    p->show();
  }
  else
  {
    ErrorPopup *p = new ErrorPopup("INVALID VALUES.\n Changes have not been applied!", "images/tiger_default.png", "OK!", 0);
    p->show();
    cTableModel->select();
  }

}

/*!
 * \brief MainWindow::Welcome
 * The welcome screen!
 */
void MainWindow::Welcome()
{
  ui->stacked_pages->setCurrentIndex(INTRO);
  WelcomeAnimation();
  QSound::play(":/sounds/tiger.wav");
}

/*!
* \brief MainWindow::Click
* Plays a classic button click sound
*/
void MainWindow::Click()
{
  QSound::play(":/sounds/click.wav");
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
          ErrorPopup *p = new ErrorPopup("CUSTOMER HAS BEEN GRANTED ACCESS TO THE PAMPHLET.");
          p->show();
        }
      }
      else
      {
        qDebug() << "INVALID QUERY!";
      }
    }
    else
    {
      ErrorPopup *p = new ErrorPopup("CUSTOMER HAS ALREADY BEEN SENT A PAMPLHET.\n"
                                     "Changes not applied.");
      p->show();
    }
  }
  else
  {
    ErrorPopup *p = new ErrorPopup("NO ROWS SELECTED.\n Please select a row first.");
    p->show();
  }
}

/*!
 * \brief MainWindow::on_customer_testimonial_slider_sliderMoved
 * Change displayed testimonial
 * \param position
 */
void MainWindow::on_customer_testimonial_slider_sliderMoved(int position)
{
  SetTestimonialView(position);
}

/*!
 * \brief MainWindow::on_customer_testimonial_slider_valueChanged
 * Change displayed testimonial
 * \param value
 */
void MainWindow::on_customer_testimonial_slider_valueChanged(int value)
{
  SetTestimonialView(value);
}

/*!
 * \brief MainWindow::on_toolBox_currentChanged
 * Initialize contents for customer pamphlet page
 * \param index
 */
void MainWindow::on_toolBox_currentChanged(int index)
{
  ui->contact_button->hide();
  switch(index){
  case CUST_PRODUCTS :
    break;
  case CUST_MAINTENANCE : InitializeMaintenance();
  case CUST_TESTIMONIALS : UpdateTestimonialList();
    break;
  case CUST_PURCHASE :
    break;
  default : break;
  }
}

/*!
 * \brief MainWindow::on_customer_products_slider_valueChanged
 * Switch the displayed product info
 * \param value
 */
void MainWindow::on_customer_products_slider_valueChanged(int value)
{
  ui->customer_products_title->setText(ProductInfoList.at(value).productName);
  ui->customer_products_webview->setUrl(ProductInfoList.at(value).html);
}

/*!
 * \brief MainWindow::on_GeneralInfoButton_clicked
 * display general info page
 */
void MainWindow::on_GeneralInfoButton_clicked()
{
  ui->InformationSpace->setSource(QUrl("qrc:/html/INFOGeneral.html"));
}

/*!
 * \brief MainWindow::on_ConceptOfOperations_clicked
 * Display concept of operations
 */
void MainWindow::on_ConceptOfOperations_clicked()
{
  ui->InformationSpace->setSource(QUrl("qrc:/html/INFOCop.html"));
}

/*!
 * \brief MainWindow::on_SupportedPlattaforms_clicked
 * Display supported Plattaforms
 */
void MainWindow::on_SupportedPlattaforms_clicked()
{
  ui->InformationSpace->setSource(QUrl("qrc:/html/INFOPlatforms.html"));
  qDebug() << ui->InformationSpace->source();
}

/*!
 * \brief MainWindow::on_RegisterButton_clicked
 * Display register page, set Regex validators for text fields.
 */
void MainWindow::on_RegisterButton_clicked()
{
  ui->stacked_pages->setCurrentIndex(REGISTER);
  ui->register_okay_button->setEnabled(false);
  ui->username_line_2->setValidator(new QRegExpValidator(QRegExp("[\\w]*")));
  ui->company_line->setValidator(new QRegExpValidator(QRegExp("[\\w\\s]*")));
}

/*!
 * \brief MainWindow::on_username_line_2_editingFinished
 */
void MainWindow::on_username_line_2_editingFinished()
{
  RegistrationCompleted();
}

/*!
 * \brief MainWindow::on_password_line_2_editingFinished
 */
void MainWindow::on_password_line_2_editingFinished()
{
  RegistrationCompleted();
}

/*!
 * \brief MainWindow::on_company_line_editingFinished
 */
void MainWindow::on_company_line_editingFinished()
{
  RegistrationCompleted();
}

/*!
 * \brief MainWindow::on_address_line_editingFinished
 */
void MainWindow::on_address_line_editingFinished()
{
  RegistrationCompleted();
}

/*!
 * \brief MainWindow::on_interest_box_currentIndexChanged
 * \param index
 */
void MainWindow::on_interest_box_currentIndexChanged(int index)
{
  RegistrationCompleted();
}

/*!
 * \brief MainWindow::on_terms_box_toggled
 * \param checked
 */
void MainWindow::on_terms_box_toggled(bool checked)
{
  RegistrationCompleted();
}

/*!
 * \brief MainWindow::on_register_okay_button_clicked
 * Attempt to register user. If successful, clear forms and set page
 * index to LOGIN page.
 */
void MainWindow::on_register_okay_button_clicked()
{
  if(Register())
  {
    Register_ClearForms();
    ui->stacked_pages->setCurrentIndex(LOGIN);
  }
  else
  {
    ErrorPopup *p = new ErrorPopup("CUSTOMER WITH SAME NAME ALREADY EXISTS.\n "
                                   "Did you forget about your account with us?");
    p->show();
  }
}

/*!
 * \brief MainWindow::on_register_cancel_button_clicked
 * Clear forms and set current page to LOGIN page.
 */
void MainWindow::on_register_cancel_button_clicked()
{
  Register_ClearForms();
  ui->stacked_pages->setCurrentIndex(LOGIN);
}

/*!
 * \brief MainWindow::on_OKgoBackLogIn_clicked
 * Set page to LOGIN page
 */
void MainWindow::on_OKgoBackLogIn_clicked()
{
  ui->stacked_pages->setCurrentIndex(LOGIN);
}

/*!
 * \brief MainWindow::on_InformationButton_clicked
 * Set current page to INFORMATION page
 */
void MainWindow::on_InformationButton_clicked()
{
  ui->stacked_pages->setCurrentIndex(INFORMATION);
  ui->GeneralInfoButton->click();
}

/*!
 * \brief MainWindow::on_admin_logout_button_clicked
 * Deallocate memory for table models and set current page to LOGIN page
 */
void MainWindow::on_admin_logout_button_clicked()
{
  ui->stacked_pages->setCurrentIndex(LOGIN);
  ui->administrator_toolBox->setCurrentIndex(0);
  delete cTableModel;
  delete tTableModel;
}

/*!
 * \brief MainWindow::on_customer_purchase_purchaseButton_clicked
 * For every box that is clicked, make a purchase. If a customer has
 * made a purchase, thank them with a friendly popUp.
 * Add their purchases to the purchase table and refresh the purchases
 * view.
 */
void MainWindow::on_customer_purchase_purchaseButton_clicked()
{
  bool madePurchase = false;

  if(ui->customer_purchase_product_checkBox->isChecked())
  {
    madePurchase = db->Purchase(activeUserId, "1");
  }
  if(ui->customer_purchase_product_checkBox_2->isChecked())
  {
    madePurchase = db->Purchase(activeUserId, "2");
  }
  if(ui->customer_purchase_product_checkBox_3->isChecked())
  {
    madePurchase = db->Purchase(activeUserId, "3");
  }
  if(ui->customer_purchase_product_checkBox_4->isChecked())
  {
    madePurchase = db->Purchase(activeUserId, "4");
  }
  if(ui->customer_purchase_product_checkBox_5->isChecked())
  {
    madePurchase = db->Purchase(activeUserId, "5");
  }
  if(madePurchase)
  {
    ClearAllPurchaseCheckboxes();
    ErrorPopup *p = new ErrorPopup("Thank you for your purchase!\n"
                                   "Our representatives will contact you in"
                                   " 2 business days. Exactly.",
                                   "images/tiger.png", "ROAR!", 0);
    p->show();
    pTableModel->select();
  }
  else
  {
    ErrorPopup *p = new ErrorPopup("NO PRODUCTS SELECTED.\n Please select "
                                   "a product to purchase.");
    p->show();
  }
}

/*!
 * \brief MainWindow::on_pushButton_2_clicked
 * Clear all checkboxes and set toolbox page to initial page.
 */
void MainWindow::on_pushButton_2_clicked()
{
  ClearAllPurchaseCheckboxes();
  ui->toolBox->setCurrentIndex(0);
}

/*!
 * \brief MainWindow::on_customer_logout_button_clicked
 * Reset all sliders and checkboxes, log the user out.
 */
void MainWindow::on_customer_logout_button_clicked()
{
  ui->contact_button->hide();
  ui->customer_products_slider->setSliderPosition(0);
  ui->customer_testimonial_slider->setSliderPosition(1);
  ui->stacked_pages->setCurrentIndex(LOGIN);
  ClearAllPurchaseCheckboxes();
  delete pTableModel;
}

/*!
 * \brief MainWindow::on_add_testimonial_buttonBox_accepted
 * Attempt to add a customer's testimonial to the Testimonial table.
 */
void MainWindow::on_add_testimonial_buttonBox_accepted()
{
  QString name = db->GetCustomerNameById(activeUserId);

  if(!ui->add_testimonial_text->toPlainText().isEmpty())
  {
    if(db->AddTestimonial(name, ui->add_testimonial_text->toPlainText()))
    {
      ErrorPopup *p = new ErrorPopup("THANK YOU FOR LEAVING A TESTIMONIAL!\n"
                                     "We hope to do good business with you in the future.");
      p->show();
      ui->toolBox->setCurrentIndex(0);
    }
    else
    {
      ErrorPopup *p = new ErrorPopup("YOU'VE ALREADY LEFT A TESTIMONIAL.\n"
                                     "Thank you!", "images/tiger_default.png", "OK!", 0);
      p->show();
    }
  }
  else
  {
    ErrorPopup *p = new ErrorPopup("THERE IS NO TESTIMONIAL.\n"
                                   "We're onto you. Enter a testimonial.",
                                   "images/tiger.png", "FINE.", 0);
    p->show();
  }
  ui->add_testimonial_text->clear();
}

/*!
 * \brief MainWindow::on_add_testimonial_text_textChanged
 * Ensure that the testimonial has no more than 500 characters.
 */
void MainWindow::on_add_testimonial_text_textChanged()
{
  if(ui->add_testimonial_text->toPlainText().length() >= 500)
  {
    ui->add_testimonial_text->textCursor().deletePreviousChar();
  }
}

/*!
 * \brief MainWindow::on_add_testimonial_buttonBox_rejected
 * Clear testimonial box and set current index to initial page.
 */
void MainWindow::on_add_testimonial_buttonBox_rejected()
{
  ui->toolBox->setCurrentIndex(0);
  ui->add_testimonial_text->clear();
}

/*!
 * \brief MainWindow::on_contact_button_clicked
 * Make a cool popup with contact info.
 */
void MainWindow::on_contact_button_clicked()
{
  ContactUs *contact = new ContactUs();
  //ui->contact_button->hide();
  contact->setWindowModality(Qt::ApplicationModal);
  contact->show();
  contact->setWindowTitle("Contact us!");

}

/*!
 * \brief MainWindow::on_customer_submit_changes_help_button_clicked
 * Display a brief "HOW TO" for using admin page 1.
 */
void MainWindow::on_customer_submit_changes_help_button_clicked()
{
  ErrorPopup *p = new ErrorPopup("All fields are editable. "
                                 "Double-click the fields on the right "
                                 "and edit away. When you're done, hit "
                                 "\"submit changes\"!");
  p->show();
}

/*!
 * \brief MainWindow::on_testimonial_add_help_button_clicked
 * Display a brief "HOW TO" for using admin page 2.
 */
void MainWindow::on_testimonial_add_help_button_clicked()
{
  ErrorPopup *p = new ErrorPopup("Click on a testimonial and then use the "
                                 "buttons to remove or approve one."
                                 "Click \"Add Testimonial\" to add a "
                                 "testimonial yourself!");
  p->show();
}

/*!
 * \brief MainWindow::on_help_button_clicked
 * Display a help menu for the entire program.
 */
void MainWindow::on_help_button_clicked()
{
  HelpOption *help = new HelpOption();
  help->setWindowModality(Qt::ApplicationModal);
  help->show();
  help->setWindowTitle("Help!");
}
