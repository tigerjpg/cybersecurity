#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QVector>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QMovie>
#include <QLabel>
#include <QSound>
#include <QList>
#include "database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT


public:
  enum Page {
    INTRO,
    REGISTER,
    LOGIN,
    INFORMATION,
    ADMINISTRATOR,
    CUSTOMER
  };

  enum CustomerPage {
    CUST_PRODUCTS,
    CUST_TESTIMONIALS,
    CUST_PURCHASE
  };

  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();


private slots:
  void on_finished_intro();
  void on_welcomeBtn_clicked();



  void on_toolBox_currentChanged(int index);

  void on_customer_testimonial_slider_sliderMoved(int position);

  void on_customer_testimonial_slider_valueChanged(int value);

private:
  void initializeCustomerView();
  bool defaultCustomerView();
  bool keyCustomerView();
  bool interestCustomerView(int i);
  bool interestAndKeyCustomerView(int i);
  void changeBackground(int index);
  void setBackground(QPixmap picture);
  void setBackground(QMovie *movie, int speed);
  void WelcomeAnimation();
  void SetTestimonialView(int index);
  void UpdateTestimonialList();
  Ui::MainWindow *ui;
  Database *db;
  QSqlTableModel *sql_table_model;
  QVector<QPixmap> mainBackground;
  QList<QSqlRecord> *testimonials;
};

#endif // MAINWINDOW_H
