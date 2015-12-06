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
  bool RegistrationCompleted();


private slots:
  void on_finished_intro();
  void on_welcomeBtn_clicked();



  void on_register_buttonBox_accepted();

  void on_username_line_2_editingFinished();

  void on_password_line_2_editingFinished();

  void on_company_line_editingFinished();

  void on_address_line_editingFinished();

  void on_interest_box_currentIndexChanged(int index);

  void on_terms_box_toggled(bool checked);

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
  Ui::MainWindow *ui;
  Database *db;
  QSqlTableModel *sql_table_model;
  QVector<QPixmap> mainBackground;
};

#endif // MAINWINDOW_H
