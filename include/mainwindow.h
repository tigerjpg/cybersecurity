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

  void on_GeneralInfoButton_clicked();

  void on_ConceptOfOperations_clicked();

  void on_SupportedPlattaforms_clicked();

  void on_RegisterButton_clicked();

  void on_OKgoBackLogIn_clicked();

  void on_InformationButton_clicked();

private:
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
