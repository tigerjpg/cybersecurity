#ifndef ADDTESTIMONIALPOPUP_H
#define ADDTESTIMONIALPOPUP_H

#include <QWidget>

namespace Ui {
class AddTestimonialPopup;
}

class AddTestimonialPopup : public QWidget
{
  Q_OBJECT

public:
  explicit AddTestimonialPopup(QWidget *parent = 0);
  ~AddTestimonialPopup();

private:
  Ui::AddTestimonialPopup *ui;
};

#endif // ADDTESTIMONIALPOPUP_H
