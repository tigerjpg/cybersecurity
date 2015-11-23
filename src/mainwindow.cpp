#include "mainwindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // Sets up window and background size, since the background has to be small in designer
  this->setFixedSize(1024,768);
  ui->backGnd->lower();
  ui->backGnd->setGeometry(0,0,this->width(),this->height());

  // load all the backgrounds into the background vectors
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
  ui->welcomeTitle->hide();
  WelcomeAnimation();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::WelcomeAnimation()
{
  ui->welcomeBtn->setEnabled(false);
  QPropertyAnimation *tigershield = new QPropertyAnimation(ui->welcomeBtn, "geometry");
  connect(tigershield, SIGNAL(finished()), this, SLOT(on_finished_intro() ));
  tigershield->setDuration(1500);
  tigershield->setStartValue(QRect(-25, -216, 1200, 1200));
  tigershield->setEndValue(QRect((1024/2)-178, (768/2)-200, 400, 400));
  tigershield->start();
}

void MainWindow::on_finished_intro()
{
  QPropertyAnimation *titlein = new QPropertyAnimation(ui->welcomeTitle, "geometry");
//  connect(titlein, SIGNAL(finished()), this, SLOT(on_finished_intro() ));
  titlein->setDuration(200);
  ui->welcomeTitle->show();
  titlein->setStartValue(QRect(262,-120,500,120));
  titlein->setEndValue(QRect(262,57,500,120));
  titlein->start();
  ui->welcomeBtn->setEnabled(true);
}

void MainWindow::TigerButton()
{
  ui->lcdNumber->display(ui->lcdNumber->intValue() + 1);
}

void MainWindow::LaserOn()
{
  setBackground(mainBackground[(qrand()%4)+1]);
}

void MainWindow::LaserOff()
{
  setBackground(mainBackground[0]);
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
