#include "addtestimonialpopup.h"
#include "ui_AddTestimonialPopup.h"

AddTestimonialPopup::AddTestimonialPopup(QWidget *parent, Database *data, TestimonialTableModel *tTableModel) :
  QWidget(parent),
  ui(new Ui::AddTestimonialPopup), model(tTableModel), db(data)
{
  ui->setupUi(this);
}

AddTestimonialPopup::~AddTestimonialPopup()
{
  delete ui;
}

void AddTestimonialPopup::on_testimonial_popup_buttonBox_accepted()
{
  if(db->AddTestimonial(ui->testimonial_popup_nameLineEdit->text(), ui->testimonial_popup_textEdit->toPlainText()))
  {
    qDebug() << "ACCEPTED!";
    ui->testimonial_popup_nameLineEdit->clear();
    ui->testimonial_popup_textEdit->clear();
    model->select();
    close();
  }
  else
  {
    qDebug() << "REJECTED!";
  }
}

