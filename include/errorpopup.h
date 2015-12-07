#ifndef ERRORPOPUP_H
#define ERRORPOPUP_H

#include <QDialog>
#include <QSound>

namespace Ui {
  class ErrorPopup;
}

class ErrorPopup : public QDialog
{
  Q_OBJECT

public:
  explicit ErrorPopup(QString message,
                      QString image  = "images/tiger.png",
                      QString button = "OK!",
                      QWidget *parent = 0);
  ~ErrorPopup();

private slots:
  void on_error_popup_button_clicked();

private:
  Ui::ErrorPopup *ui;
};

#endif // ERRORPOPUP_H
