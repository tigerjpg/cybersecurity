#include "addtestimonialpopup.h"
#include "ui_AddTestimonialPopup.h"

AddTestimonialPopup::AddTestimonialPopup(QWidget *parent, Database *data, TestimonialTableModel *tTableModel) :
  QWidget(parent),
  ui(new Ui::AddTestimonialPopup), model(tTableModel), db(data)
{
  ui->setupUi(this);
  ui->testimonial_popup_nameLineEdit->setValidator(new QRegExpValidator(QRegExp("[\\w\\s]*"), this));
}

AddTestimonialPopup::~AddTestimonialPopup()
{
  delete ui;
}

void AddTestimonialPopup::on_testimonial_popup_buttonBox_accepted()
{
  if(!ui->testimonial_popup_nameLineEdit->text().isEmpty() &&
     !ui->testimonial_popup_textEdit->toPlainText().isEmpty())
  {
    if(ui->testimonial_popup_nameLineEdit->hasAcceptableInput())
    {
      if(db->AddTestimonial(ui->testimonial_popup_nameLineEdit->text(),
                            ui->testimonial_popup_textEdit->toPlainText()))
      {
        qDebug() << "TESTIMONIAL ACCEPTED!";
        ui->testimonial_popup_nameLineEdit->clear();
        ui->testimonial_popup_textEdit->clear();
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


void AddTestimonialPopup::on_testimonial_popup_buttonBox_rejected()
{
  model->select();
  close();
}

void AddTestimonialPopup::on_testimonial_popup_textEdit_textChanged()
{
    if(ui->testimonial_popup_textEdit->toPlainText().length() >= 500)
    {
      ui->testimonial_popup_textEdit->textCursor().deletePreviousChar();
    }
}
