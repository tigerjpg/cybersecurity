#include "include/contactus.h"
#include "ui_contactus.h"

ContactUs::ContactUs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContactUs)
{
    ui->setupUi(this);
}

ContactUs::~ContactUs()
{
    delete ui;
}

void ContactUs::on_OKEscapeContactUs_clicked()
{
  this->close();
}
