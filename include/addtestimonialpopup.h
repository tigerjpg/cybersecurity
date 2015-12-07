#ifndef ADDTESTIMONIALPOPUP_H
#define ADDTESTIMONIALPOPUP_H

#include <QWidget>
#include "testimonialtablemodel.h"
#include "database.h"
#include "errorpopup.h"

namespace Ui {
class AddTestimonialPopup;
}

class AddTestimonialPopup : public QWidget
{
  Q_OBJECT

public:
  explicit AddTestimonialPopup(QWidget *parent = 0, Database *data = 0, TestimonialTableModel *tTableModel = 0);
  ~AddTestimonialPopup();

private slots:
  void on_testimonial_popup_buttonBox_accepted();

  void on_testimonial_popup_buttonBox_rejected();

  void on_testimonial_popup_textEdit_textChanged();

private:
  Ui::AddTestimonialPopup *ui;
  TestimonialTableModel *model;
  Database *db;
};

#endif // ADDTESTIMONIALPOPUP_H
