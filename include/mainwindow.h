#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QVector>
#include <QPixmap>

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

private:
  void changeBackground(int index);
  Ui::MainWindow *ui;
  QVector<QPixmap> mainBackground;
};

#endif // MAINWINDOW_H
