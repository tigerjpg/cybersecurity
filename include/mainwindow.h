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

private:
  Ui::MainWindow *ui;
  Database *db;
  CustomerTableModel *cTableModel;
  QVector<QPixmap> mainBackground;
};

#endif // MAINWINDOW_H
