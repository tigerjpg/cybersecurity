#include "addtestimonialpopup.h"
#include "ui_AddTestimonialPopup.h"

AddTestimonialPopup::AddTestimonialPopup(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::AddTestimonialPopup)
{
  ui->setupUi(this);
}

AddTestimonialPopup::~AddTestimonialPopup()
{
  delete ui;
}
