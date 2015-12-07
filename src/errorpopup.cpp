#include "errorpopup.h"
#include "ui_errorpopup.h"

ErrorPopup::ErrorPopup(QString message, QString image, QString button, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ErrorPopup)
{
  ui->setupUi(this);

  QPixmap errorImage(image);
  errorImage = errorImage.scaled(118,129, Qt::KeepAspectRatio);
  ui->error_popup_message->setText(message);
  ui->error_popup_picture->setPixmap(QPixmap(errorImage));
  ui->error_popup_button->setText(button);
}

ErrorPopup::~ErrorPopup()
{
  delete ui;
}

void ErrorPopup::on_error_popup_button_clicked()
{
  QSound::play(":/sounds/click.wav");
  close();
}
