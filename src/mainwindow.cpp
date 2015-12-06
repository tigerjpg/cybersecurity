#include "mainwindow.h"
#include "ui_MainWindow.h"
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  db = new Database("./data/data.db", "QSQLITE");
  this->setFixedSize(800,600);

  ui->stacked_pages->setCurrentIndex(CUSTOMER);

  UpdateTestimonialList();

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

void MainWindow::SetTestimonialView(int index)
{
  if(index >= 0 && index < testimonials->size())
  {
    QPixmap image( "images/" + testimonials->at(index).field("image").value().toString() );
    image = image.scaled(ui->customer_testimonials_picture->width(), ui->customer_testimonials_picture->height(), Qt::KeepAspectRatio);

    ui->customer_testimonials_text->setText( testimonials->at(index).field("testimonial").value().toString() );
    ui->customer_testimonials_picture->setPixmap(image);
//    qDebug() << "TESTIMONIAL TEXT: " << testimonials->at(position).field("testimonial").value().toString();
//    qDebug() << "TESTIMONIAL IMAGE PATH: " << testimonials->at(position).field("image").value().toString();
  }
  else
  {
    qDebug() << "***** INVALID TESTIMONIAL INDEX!!! ******";
  }
}

void MainWindow::UpdateTestimonialList()
{
  delete testimonials;
  testimonials = db->GetData("testimonials");
  qDebug() << "TESTIMONIALS LIST SIZE: " << testimonials->size();
  ui->customer_testimonial_slider->setMinimum(0);
  ui->customer_testimonial_slider->setMaximum(testimonials->size()-1);
  SetTestimonialView(ui->customer_testimonial_slider->value());
}

void MainWindow::on_finished_intro()
{
  QPropertyAnimation *titlein = new QPropertyAnimation(ui->welcomeTitle, "geometry");
  titlein->setDuration(200);
  ui->welcomeTitle->show();
  titlein->setStartValue(QRect(262,-120,500,120));
  titlein->setEndValue(QRect(262,57,500,120));
  titlein->start();
  ui->welcomeBtn->setEnabled(true);
}


void MainWindow::on_welcomeBtn_clicked()
{}

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

void MainWindow::on_customer_testimonial_slider_sliderMoved(int position)
{
  SetTestimonialView(position);
}

void MainWindow::on_customer_testimonial_slider_valueChanged(int value)
{
  SetTestimonialView(value);
}

void MainWindow::on_toolBox_currentChanged(int index)
{
    switch(index){
      case CUST_PRODUCTS : break;
      case CUST_TESTIMONIALS : UpdateTestimonialList();
                               break;
      case CUST_PURCHASE : break;
      default : break;
      }
}
