#include "include/helpoption.h"
#include "ui_helpoption.h"

HelpOption::HelpOption(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpOption)
{
    ui->setupUi(this);
    ui->HelpDisplayBox->setSource(QUrl("qrc:/html/help1.html"));
//    ui->HelpDisplayBox->setStyleSheet(":/html/styles.css");
}

HelpOption::~HelpOption()
{
    delete ui;
}

void HelpOption::on_OKExitHelpB_clicked()
{
    this->close();
}

void HelpOption::on_LogInInstructions_clicked()
{
    QString logInstructions = "To Enter the Pamphlet\n"
                              "\t-Enter Username and Password"
        "In case you don not have an existing account, Click on the Register Button.\n"

        "To Register\n"
            "\t-Fill in all of the blanks in the window, agree to the user terms"
             "by clicking the input box, then click OK.\n"
           "When You Log in into the user window, you will be able to see\n"
            "\t-Products\n"
            "\t-Testimonials\n"
            "\t-Purchase car\n";

    ui->HelpDisplayBox->setText(logInstructions);

}

void HelpOption::on_RequestPamInstructions_clicked()
{
     QString requestInstructions = "To request a copy of the panphlet\n"
                                "\t-The pamphlet is requested in the log in window, it is send automatically\n"
                                 "\twhen signin up for the pamphlet.\n";

     ui->HelpDisplayBox->setText(requestInstructions);
}

void HelpOption::on_ReadTestimonialsInstructions_clicked()
{
    QString readTestimonials = "To see other costumer's testimonials\n"
            "\t-Click on testimonials tab\n"
            "\t-To navigate slide or click along the slicing line.\n";

    ui->HelpDisplayBox->setText(readTestimonials);
}

void HelpOption::on_PurchaseInstructions_clicked()
{
    QString PurchaseInstructions = "To see products\n"
            "\t-Click on costumer products tab, and navigate the products\n"
             "\tby clicling along the slicing line.\n";

    ui->HelpDisplayBox->setText(PurchaseInstructions);
}

void HelpOption::on_LogOffInstructions_clicked()
{
    QString logoff =  "To Log Off\n"
           "\t-Click on the log off button, it will direct you to the log in screen.";

    ui->HelpDisplayBox->setText(logoff);
}

void HelpOption::on_AboutUsInstructions_clicked()
{
    QString aboutUs = "To Know about the company\n"
            "-Click on 'About Us' on the log in window.\n"
            "-Click the button 'General Info','Concept of Operations', or"
            " 'Supported Plattaforms' to see any of this options on the text"
             "display.\n";

    ui->HelpDisplayBox->setText(aboutUs);
}
