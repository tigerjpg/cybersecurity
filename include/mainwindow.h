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
<<<<<<< HEAD
#include "customertablemodel.h"
=======
>>>>>>> 93cbac2e03dff5cb3206f681c9d4feadbbb4b9d4

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  enum Page
  {
    LOGIN,
    ADMIN,
    MAIN
  };

  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

public slots:
  void TigerButton();
  void LaserOn();
  void LaserOff();

private slots:
  void on_finished_intro();
  void on_page0_clicked();
  void on_page1_clicked();
  void on_page2_clicked();
  void on_page3_clicked();
  void on_page4_clicked();
  void on_welcomeBtn_clicked();

  void on_ok_button_clicked();

  void on_clear_button_clicked();

  void on_passwordBox_returnPressed();

  void on_checkBox_toggled(bool checked);

  void on_testimonial_slider_valueChanged(int value);

private:
  void changeBackground(int index);
  void setBackground(QPixmap picture);
  void setBackground(QMovie *movie, int speed);
  void WelcomeAnimation();
  Ui::MainWindow *ui;
  Database *db;
  CustomerTableModel *cTableModel;
  QVector<QPixmap> mainBackground;
};

#endif // MAINWINDOW_H
