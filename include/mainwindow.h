#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QVector>
#include <QPixmap>
#include "database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

public slots:
  void TigerButton();
  void LaserOn();
  void LaserOff();

private slots:
  void on_page0_clicked();
  void on_page1_clicked();
  void on_page2_clicked();
  void on_page3_clicked();
  void on_page4_clicked();

  void on_ok_button_clicked();

  void on_clear_button_clicked();

  void on_passwordBox_returnPressed();

  void on_usernameBox_returnPressed();

  void on_checkBox_stateChanged(int arg1);

  void on_interest_level_box_activated(int index);

private:
  void initializeCustomerView();
  bool defaultCustomerView();
  bool keyCustomerView();
  bool interestCustomerView(int i);
  bool interestAndKeyCustomerView(int i);
  void changeBackground(int index);
  Ui::MainWindow *ui;
  Database *db;
  QSqlTableModel *sql_table_model;
  QVector<QPixmap> mainBackground;
};

#endif // MAINWINDOW_H
