#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QVector>
#include <QPixmap>
//#include <QPropertyAnimation>
//#include <QMovie>
#include <QLabel>
#include <QSound>
#include "database.h"
#include "customertablemodel.h"
#include "testimonialtablemodel.h"
#include "addtestimonialpopup.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  enum Page
  {
    LOGIN,
    REGISTER,
    INFO,
    ADMIN,
    CUSTOMER
  };

  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

public slots:

private slots:

  void on_login_buttonBox_accepted();

  void on_login_buttonBox_rejected();

  void on_customer_tableView_activated(const QModelIndex &index);

  void on_password_line_returnPressed();

  void on_key_customers_checkBox_toggled(bool checked);

  void on_administrator_toolBox_currentChanged(int index);

  void on_testimonial_add_button_clicked();

  void on_testimonial_remove_button_clicked();

  void on_testimonial_approve_button_clicked();

  void on_customer_remove_button_clicked();

private:
  Ui::MainWindow *ui;
  Database *db;
  CustomerTableModel *cTableModel;
  TestimonialTableModel *tTableModel;
  QVector<QPixmap> mainBackground;
  void InitTestimonialTableView();
};

#endif // MAINWINDOW_H
