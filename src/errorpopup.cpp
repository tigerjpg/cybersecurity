#include "errorpopup.h"
#include "ui_errorpopup.h"

ErrorPopup::ErrorPopup(QString message, QString image, QString button, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ErrorPopup)
{
  ui->setupUi(this);
  this->setWindowTitle("ROAR!");
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

/*!
 * \brief ErrorPopup::on_error_popup_button_clicked
 * Play a fun click sound! (Sometimes :| )
 */
void ErrorPopup::on_error_popup_button_clicked()
{
  QSound::play(":/sounds/click.wav");
  close();
}
