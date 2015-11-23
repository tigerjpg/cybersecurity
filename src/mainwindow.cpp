#include "mainwindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // load all the backgrounds into the background vectors
  mainBackground.append(QPixmap(":/images/tiger.jpg"));
  mainBackground.append(QPixmap(":/images/tiger2.jpg"));
  mainBackground.append(QPixmap(":/images/tiger3.jpg"));
  mainBackground.append(QPixmap(":/images/tiger4.jpg"));
  mainBackground.append(QPixmap(":/images/tiger5.jpg"));

  // load the images into buttons
  qDebug() << "Setting button images: " << ui->pushButton->SetButtonImage(":/images/tiger.png",
                                                                          ":/images/tiger-hover.png",
                                                                          ":/images/tiger-click.png");

  //Welcome Screen
  WelcomeAnimation();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::WelcomeAnimation()
{
  ui->MainView->setCurrentIndex(0);

  // Create and start the animated wallpaper
  QMovie *matrix  = new QMovie(":/images/slowmatrix.gif");
  QLabel *backGnd = new QLabel(ui->MainView->currentWidget());
  matrix->setSpeed(50);
  backGnd->setMovie(matrix);
  matrix->start();

  // Create and set up the welcome button
  imagebutton *startButton = new imagebutton(ui->MainView->currentWidget());
  connect(startButton, SIGNAL(clicked(bool)), this, SLOT(on_welcome_clicked()));
  startButton->setGeometry(0,0,1024,768);
  //startButton->setEnabled(false);
  qDebug() << "welcome button: " << startButton->SetButtonImage(":/images/welcome.png",
                                                                ":/images/welcome-hover.png",
                                                                ":/images/welcome-click.png");

  // Animate the button
  QPropertyAnimation *animation = new QPropertyAnimation(startButton, "geometry");
  connect(animation, SIGNAL(finished()), this, SLOT(on_finished_intro() ));
  animation->setDuration(1500);
  animation->setStartValue(QRect(0, 0, 1024, 768));
  animation->setEndValue(QRect((1024/2)-170, (768/2)-200, 400, 400));
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

void MainWindow::on_welcome_clicked()
{
  ui->MainView->setCurrentIndex(1);
  on_page0_clicked();
}

void MainWindow::on_finished_intro()
{

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
