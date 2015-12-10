#include "addcustomerpopup.h"
#include "ui_AddCustomerPopup.h"

AddCustomerPopup::AddCustomerPopup(QWidget *parent, Database *db, CustomerTableModel *cTableModel) :
  QWidget(parent),
  ui(new Ui::AddCustomerPopup), model(cTableModel), data(db)
{
  ui->setupUi(this);
  this->setWindowTitle("Add Customer");
    ui->add_customer_name_box->setValidator(new QRegExpValidator(QRegExp("[\\w\\s]*"), this));
    ui->add_customer_address_box->setValidator(new QRegExpValidator(QRegExp("[\\w\\s]*"), this));
}

AddCustomerPopup::~AddCustomerPopup()
{
  delete ui;
}

/*!
 * \brief AddCustomerPopup::on_add_customer_buttonBox_accepted
 * Verify that fields have values, and attempt to add a user to the
 * Database.
 */
void AddCustomerPopup::on_add_customer_buttonBox_accepted()
{
  QString password = ui->add_customer_password_box->text();

  if(!ui->add_customer_username_box->text().isEmpty() &&
     !ui->add_customer_name_box->text().isEmpty() &&
     !ui->add_customer_address_box->text().isEmpty())
  {
    if(ui->add_customer_username_box->hasAcceptableInput() &&
       ui->add_customer_name_box->hasAcceptableInput() &&
       ui->add_customer_address_box->hasAcceptableInput())
    {
      if(data->AddCustomer(ui->add_customer_name_box->text(),
                           ui->add_customer_address_box->text(),
                           QString::number(ui->add_customer_interest_comboBox->currentIndex()),
                           QString::number(ui->add_customer_key_checkBox->isChecked()),
                           QString::number(ui->add_customer_sent_checkBox->isChecked())))
      {
        qDebug() << "CUSTOMER ACCEPTED!";
        data->AddUser(data->GetCustomerIdByName(ui->add_customer_name_box->text()),
                                                ui->add_customer_username_box->text(),
                                                password);
        ui->add_customer_name_box->clear();
        ui->add_customer_address_box->clear();
        ui->add_customer_interest_comboBox->clear();
        model->select();
        close();
      }
      else
      {
        ErrorPopup *p = new ErrorPopup("CUSTOMER WITH THE SAME NAME ALREADY EXISTS.",
                                       "images/tiger_default.png", "OK!", 0);
        p->show();
      }
    }
  }
  else
  {
    ErrorPopup *p = new ErrorPopup("FIELDS CANNOT BE LEFT BLANK.\n"
                                   "Enter some data.", "images/tiger_default.png",
                                   "Thanks", 0);
    p->show();
  }
}


/*!
 * \brief AddCustomerPopup::on_add_customer_buttonBox_rejected
 * Close the window.
 */
void AddCustomerPopup::on_add_customer_buttonBox_rejected()
{
    close();
}
