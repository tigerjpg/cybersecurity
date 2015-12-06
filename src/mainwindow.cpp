#include "mainwindow.h"
#include "ui_MainWindow.h"
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  db = new Database("./data/data.db", "QSQLITE");
  this->setFixedSize(800,600);

  ui->stacked_pages->setCurrentIndex(LOGIN);

}

MainWindow::~MainWindow()
{
  delete ui;
}

bool MainWindow::RegistrationCompleted()
{
  if(!ui->username_label_2->text().isEmpty() &&
     !ui->password_label_2->text().isEmpty() &&
     !ui->company_line->text().isEmpty() &&
     !ui->address_line->text().isEmpty() &&
     ui->interest_box->currentIndex() > 0 &&
     ui->terms_box->isChecked())
  {
    qDebug() << "registration complete\n";
    ui->register_okay_button->setEnabled(true);
    return true;
  }
  else
  {
    qDebug() << "registration incomplete\n";
    ui->register_okay_button->setEnabled(false);
    return false;
  }
}

void MainWindow::Register()
{
  if(db->AddUser(ui->username_line_2->text(), ui->password_line_2->text(), "false"))
  {
    qDebug() << ui->username_line_2->text() << " added the the users table.\n";
  }
  if(db->AddCustomer(ui->company_line->text(), ui->address_line->text(),
                  QString::number(ui->interest_box->currentIndex()-1), "false"))
  {
    qDebug() << ui->company_line->text() << " added to the customer table.\n";
  }
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


void MainWindow::on_welcomeBtn_clicked()
{
}

void MainWindow::on_GeneralInfoButton_clicked()
{
    QString generalInfo = "T.I.G.E.R Inc\n\n"
                          "Address: 3 Cheetah Avenue, Irvine, C.A 92614\n"
                          "Phone Number: 949-420-6969\n"
                          "Email Address: TigerInc@Tiger.cjpg\n\n";
    QString missionStatement = "Our Mission:\n\n"
                               "This company was created by Ernest L. Cheetahiser in January, 1991."
                               "The reason to create this company was to provide the public with solutions "
                               "to new cyber security threats. "
                               "We want to make the business world safe and reliable in order to have a more "
                               "stable market and economy.\n\n";

    QString whatWeDo = "What We Do: \n\n"
                       "We create all kinds of solutions to cyberthreats."
                       " We create products that prevent data leaks from within and outside the company. "
                       "We also create environments that fight cyber attackers and provide ways to know the source "
                       "of the issue so future attacks can be prevented. The company has in it's mind that time"
                       " is precious, that is why we provide the fastest and most reliable technical and costumer service in the market. "
                       "We care and protect our costumers better than ourselves\n\n.";

    QString howWeDo = "How We do it:\n\n"
                      "We use cutting edge technology for our systems as well as the most efficient software. "
                      "Our development team makes sure that the data we manage is always safe and our software "
                      "not interfering with the traffic. Because we care about our clients, we have meetings with company "
                      "employees to find ways to improve our services and products.\n\n";



    //ui->information_text->setText(generalInfo);

    ui->InformationSpace->setText(generalInfo + missionStatement + whatWeDo + howWeDo);

}

void MainWindow::on_ConceptOfOperations_clicked()
{
    QString conceptOfOperations = "Concept Of Operations\n\n"
                                  "TIGER products are delivered within 2 business day of purchase. TIGER's Technitians come to the"
            "costumer, take control of all the hardware necessary to install the purchased products. Upon installation, the"
            "company will provide the services promised in time matter. The company will run a test to see if the software"
            "is working as intended. In case of a fail in the test, TIGER will fix the issue without any additional cost, just"
            "as specified in the policy. TIGER installs the systems within 48 hours. It requires that the costumer provides all"
           " the current security details of the server. Nothing will be changed, instead, more security features will be"
            "install on top of the curent. Tiger keeps a data base of employees and contacts them every quarter to see if the systems"
            "are up to date, or to discuss contract clauses.\n\n";

    ui->InformationSpace->setText(conceptOfOperations);
}

void MainWindow::on_SupportedPlattaforms_clicked()
{
    QString plattaforms =   "Supported Plattaforms\n\n"
                            "Ubuntu\n"
                            "Debian\n"
                            "Mint\n"
                            "Fedora\n"
                            "CentOs/Red Hat Enterprise Linux\n"
                            "openSUSE/SUSE Linux Enterprise\n"
                            "Mageia/Mandriva\n"
                            "Arch Linux\n"
                            "Slackware Linux\n\n"

                            "Others:\n\n"

                            "none\n\n"

                            "Hardware (Minimum):\n\n"

                                "Intel® Xeon®\n"
                                "500 TB of Memory";

    ui->InformationSpace->setText(plattaforms);
}

void MainWindow::on_RegisterButton_clicked()
{
    ui->stacked_pages->setCurrentIndex(REGISTER);
    ui->register_okay_button->setEnabled(false);
    ui->username_line_2->setValidator(new QRegExpValidator(QRegExp("[\\w]*")));
    ui->company_line->setValidator(new QRegExpValidator(QRegExp("[\\w\\s]*")));
}

void MainWindow::on_username_line_2_editingFinished()
{
    RegistrationCompleted();
}

void MainWindow::on_password_line_2_editingFinished()
{
  RegistrationCompleted();
}

void MainWindow::on_company_line_editingFinished()
{
  RegistrationCompleted();
}

void MainWindow::on_address_line_editingFinished()
{
  RegistrationCompleted();
}

void MainWindow::on_interest_box_currentIndexChanged(int index)
{
  RegistrationCompleted();
}

void MainWindow::on_terms_box_toggled(bool checked)
{
  RegistrationCompleted();
}

void MainWindow::on_register_okay_button_clicked()
{
  Register();
  ui->stacked_pages->setCurrentIndex(LOGIN);
}

void MainWindow::on_register_cancel_button_clicked()
{
  // Maybe forms need to be cleared.
  ui->stacked_pages->setCurrentIndex(LOGIN);
}

void MainWindow::on_OKgoBackLogIn_clicked()
{
    ui->stacked_pages->setCurrentIndex(LOGIN);
}

void MainWindow::on_InformationButton_clicked()
{
    ui->stacked_pages->setCurrentIndex(INFORMATION);
}
