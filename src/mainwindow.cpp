#include "mainwindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  this->setFixedSize(1024,768);

  // load all the backgrounds into the background vectors
  ui->backGnd->lower();
  mainBackground.append(QPixmap(":/images/tiger.jpg"));
  mainBackground.append(QPixmap(":/images/tiger2.jpg"));
  mainBackground.append(QPixmap(":/images/tiger3.jpg"));
  mainBackground.append(QPixmap(":/images/tiger4.jpg"));
  mainBackground.append(QPixmap(":/images/tiger5.jpg"));

  // load the images into buttons
  qDebug() << "Setting button1: " << ui->pushButton->SetButtonImage(":/images/tiger.png",
                                                                          ":/images/tiger-hover.png",
                                                                          ":/images/tiger-click.png");
  qDebug() << "Setting WelcomeBtn: " << ui->welcomeBtn->SetButtonImage(":/images/welcome.png",
                                                                   ":/images/welcome-hover.png",
                                                                   ":/images/welcome-click.png");

  //Welcome Screen
  ui->MainView->setCurrentIndex(0);
  setBackground(new QMovie(":/images/slowmatrix.gif"), 50);
  WelcomeAnimation();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::WelcomeAnimation()
{
  ui->welcomeBtn->setEnabled(false);
  QPropertyAnimation *animation = new QPropertyAnimation(ui->welcomeBtn, "geometry");
  connect(animation, SIGNAL(finished()), this, SLOT(on_finished_intro() ));
  animation->setDuration(1500);
  animation->setStartValue(QRect(-25, -216, 1200, 1200));
  animation->setEndValue(QRect((1024/2)-178, (768/2)-200, 400, 400));
  animation->start();
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

void MainWindow::setBackground(QPixmap picture)
{
  this->setFixedSize(QSize(picture.width(), picture.height() ));
  ui->backGnd->setPixmap(picture);
}

void MainWindow::setBackground(QMovie *movie, int speed)
{
  if(movie->isValid())
  {
      movie->setSpeed(speed);
      movie->setScaledSize(QSize(this->width(), this->height()));
      ui->backGnd->setMovie(movie);
      movie->start();
  }
}

void MainWindow::on_finished_intro()
{
  ui->welcomeBtn->setEnabled(true);
}

void MainWindow::on_page0_clicked()
{
  ui->stackedWidget->setCurrentIndex(0);
  setBackground(mainBackground[0]);
}

void MainWindow::on_page1_clicked()
{
  ui->stackedWidget->setCurrentIndex(1);
  setBackground(mainBackground[1]);
}

void MainWindow::on_page2_clicked()
{
  ui->stackedWidget->setCurrentIndex(2);
  setBackground(mainBackground[2]);
}

void MainWindow::on_page3_clicked()
{
  ui->stackedWidget->setCurrentIndex(3);
  setBackground(mainBackground[3]);
}

void MainWindow::on_page4_clicked()
{
  ui->stackedWidget->setCurrentIndex(4);
  setBackground(mainBackground[4]);
}

void MainWindow::on_welcomeBtn_clicked()
{
  ui->MainView->setCurrentIndex(1);
  on_page0_clicked();
}
