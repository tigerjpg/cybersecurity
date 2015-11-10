#include "mainwindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  QPixmap background(":/images/tiger.jpg");
  this->setFixedSize(QSize( background.width(), background.height() ));
  QPalette backgroundBrush;
  backgroundBrush.setBrush(QPalette::Background, background);
  this->setPalette(backgroundBrush);

  qDebug() << "Setting Button image: " << ui->pushButton->SetButtonImage(":/images/tiger.png") << endl;
  qDebug() << "Setting Hover image: " << ui->pushButton->SetHoverImage(":/images/tiger-hover.png") << endl;
  qDebug() << "Setting Click image: " << ui->pushButton->SetClickImage(":/images/tiger-click.png") << endl;
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
