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
        qDebug() << "TESTIMONIAL REJECTED!";
      }
    }
  }
  else
  {
    qDebug() << "TEXT BOXES CANNOT BE EMPTY!!";
  }
}



void AddCustomerPopup::on_add_customer_buttonBox_rejected()
{
    close();
}
