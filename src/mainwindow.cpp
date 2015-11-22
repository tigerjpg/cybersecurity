#include "mainwindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  QPixmap background(":/images/tiger.jpg");
  this->setFixedSize(background.width(), background.height());
  QPalette backgroundBrush;
  backgroundBrush.setBrush(QPalette::Background, background);
  this->setPalette(backgroundBrush);

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
