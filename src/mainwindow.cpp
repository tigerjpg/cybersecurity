#include "mainwindow.h"
#include "ui_MainWindow.h"
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  db = new Database("./data/data.db", "QSQLITE");

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

// This is going to be admin page FOR NOW
// TODO rename button and page to represent page function NOT number
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
  // TODO set max to testimonial table size
  //  needs that function from db
  ui->testimonial_slider->setRange(1,5);
  ui->testimonial_slider->setValue(1);
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

void MainWindow::on_ok_button_clicked()
{
  ui->login_error_message->setStyleSheet("QLabel { "
                                           "font: bold; "
                                           "font-size: 18px; "
                                           "text-align: center; "
                                           "color : palette(highlight);  }");
    if(!ui->usernameBox->text().isEmpty() && !ui->passwordBox->text().isEmpty())
    {
      initializeCustomerView();
      if(db->Authenticate(ui->usernameBox->text(), ui->passwordBox->text()))
      {
        ui->usernameBox->clear();
        ui->passwordBox->clear();
        // TODO needs to go to a specific page, ints tend to change
        ui->stackedWidget->setCurrentIndex(1);
      }
      else
      {
        ui->usernameBox->clear();
        ui->passwordBox->clear();
        ui->login_error_message->setText("Invalid login credentials.");
      }
    }
    else
    {
      ui->login_error_message->setText("Please enter your credentials.");
    }
}

void MainWindow::on_clear_button_clicked()
{
  ui->usernameBox->clear();
  ui->passwordBox->clear();
}

void MainWindow::on_passwordBox_returnPressed()
{
  ui->ok_button->click();
}

void MainWindow::on_usernameBox_returnPressed()
{

}

bool MainWindow::defaultCustomerView()
{
  sql_table_model->setTable("customers");
  return sql_table_model->select();
}

bool MainWindow::keyCustomerView()
{
  sql_table_model->setTable("customers");
  sql_table_model->setFilter("key = \"1\"");
  return sql_table_model->select();
}

bool MainWindow::interestCustomerView(int i)
{
  QString interest = QString::number(i);
  sql_table_model->setTable("customers");
  sql_table_model->setFilter("interest = \"" + interest + "\";");
  return sql_table_model->select();
}

bool MainWindow::interestAndKeyCustomerView(int i)
{
  QString interest = QString::number(i);
  sql_table_model->setTable("customers");
  sql_table_model->setFilter("key = \"1\" and interest = \"" + interest + "\";");
  return sql_table_model->select();
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
  switch(arg1)
  {
  case 0:
    switch(ui->interest_level_box->currentIndex())
    {
    case 0:
      defaultCustomerView();
      break;
    case 1:
    case 2:
    case 3:
      interestCustomerView(ui->interest_level_box->currentIndex() - 1);
    }
    break;
  case 2:
    switch(ui->interest_level_box->currentIndex())
    {
    case 0:
      keyCustomerView();
      break;
    case 1:
    case 2:
    case 3:
      interestAndKeyCustomerView(ui->interest_level_box->currentIndex() - 1);
    }
    break;
  }
}

void MainWindow::initializeCustomerView()
{
  ui->stackedWidget->setCurrentIndex(3);
  sql_table_model = new QSqlTableModel(this, *db);
  defaultCustomerView();
  ui->customer_view->setModel(sql_table_model);
  ui->customer_view->hideColumn(0);
  ui->customer_view->hideColumn(3);
  ui->customer_view->hideColumn(4);
  ui->customer_view->resizeColumnsToContents();
  ui->customer_view->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::on_interest_level_box_activated(int index)
{
  if(ui->checkBox->isChecked())
  {
    switch(index)
    {
    case 0:
      keyCustomerView();
      break;
    case 1:
    case 2:
    case 3:
      interestAndKeyCustomerView(index - 1);
    }
  }
  else
  {
    switch(index)
    {
    case 0:
      defaultCustomerView();
      break;
    case 1:
    case 2:
    case 3:
      interestCustomerView(index - 1);
    }
  }
}

void MainWindow::on_testimonial_slider_valueChanged(int value)
{
  ui->testimonial_text->setText(db->getTestimonialAtIndex(value));
  ui->testimonial_image->setPixmap(QPixmap::fromImage(QImage(":/images/" + db->getImageAtIndex(value)).scaled(ui->testimonial_image->size())));
}
