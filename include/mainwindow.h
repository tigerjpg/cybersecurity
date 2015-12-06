#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QVector>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QMovie>
#include <QLabel>
#include <QSound>
#include "database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT


public:
  enum Page {
    INTRO,
    LOGIN,
    REGISTER,
    INFORMATION,
    ADMINISTRATOR,
    CUSTOMER
  };

  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();




private slots:
  void on_finished_intro();
  void on_welcomeBtn_clicked();

  // SLOTS-Registrations fields-----------------------
  void on_username_line_2_editingFinished();
  void on_password_line_2_editingFinished();
  void on_company_line_editingFinished();
  void on_address_line_editingFinished();
  void on_interest_box_currentIndexChanged(int index);
  void on_terms_box_toggled(bool checked);
  //--------------------------------------------------

  void on_register_okay_button_clicked();

private:
  // Function to check if all fields in the registration table are filled
  bool RegistrationCompleted();
  void Register();

  void initializeCustomerView();
  bool defaultCustomerView();
  bool keyCustomerView();
  bool interestCustomerView(int i);
  bool interestAndKeyCustomerView(int i);
  void changeBackground(int index);
  void setBackground(QPixmap picture);
  void setBackground(QMovie *movie, int speed);
  void WelcomeAnimation();
  Ui::MainWindow *ui;
  Database *db;
  QSqlTableModel *sql_table_model;
  QVector<QPixmap> mainBackground;
};

#endif // MAINWINDOW_H
