#include "mainwindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  db = new Database("./data/data.db", "QSQLITE");
  ui->setupUi(this);

  // load all the backgrounds into the background vectors
  mainBackground.append(QPixmap(":/images/tiger.jpg"));
  mainBackground.append(QPixmap(":/images/tiger2.jpg"));
  mainBackground.append(QPixmap(":/images/tiger3.jpg"));
  mainBackground.append(QPixmap(":/images/tiger4.jpg"));
  mainBackground.append(QPixmap(":/images/tiger5.jpg"));

  // set the default view
  on_page1_clicked();

  // load the images into buttons
  qDebug() << "Setting button images: " << ui->pushButton->SetButtonImage(":/images/tiger.png", ":/images/tiger-hover.png", ":/images/tiger-click.png");
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::TigerButton()
{
  ui->lcdNumber->display(ui->lcdNumber->intValue() + 1);
}

void MainWindow::LaserOn()
{
  QPixmap background(":/images/tiger2.jpg");
  QPalette backgroundBrush;
  backgroundBrush.setBrush(QPalette::Background, background);
  this->setPalette(backgroundBrush);
}

void MainWindow::LaserOff()
{
  QPixmap background(":/images/tiger.jpg");
  QPalette backgroundBrush;
  backgroundBrush.setBrush(QPalette::Background, background);
  this->setPalette(backgroundBrush);
}

void MainWindow::changeBackground(int index)
{
  // ensure that the index is always in range
  index %= mainBackground.size();

  // set the window size and paint the background
  this->setFixedSize(QSize( mainBackground[index].width(), mainBackground[index].height() ));
  QPalette backgroundBrush;
  backgroundBrush.setBrush(QPalette::Background, mainBackground[index]);
  this->setPalette(backgroundBrush);
}

void MainWindow::on_page0_clicked()
{
  ui->stackedWidget->setCurrentIndex(0);
  changeBackground(0);
}

void MainWindow::on_page1_clicked()
{
  ui->stackedWidget->setCurrentIndex(1);
  changeBackground(1);
}

void MainWindow::on_page2_clicked()
{
  ui->stackedWidget->setCurrentIndex(2);
  changeBackground(2);
  ui->testimonial_text->setText();
}

void MainWindow::on_page3_clicked()
{
  ui->stackedWidget->setCurrentIndex(3);
  changeBackground(3);
}

void MainWindow::on_page4_clicked()
{
  ui->stackedWidget->setCurrentIndex(4);
  changeBackground(4);
}
