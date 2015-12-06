#include "include/helpoption.h"
#include "ui_helpoption.h"

HelpOption::HelpOption(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpOption)
{
    ui->setupUi(this);
}

HelpOption::~HelpOption()
{
    delete ui;
}

void HelpOption::on_OKExitHelpB_clicked()
{
    ui->EverythingHelpstackedWidget->close();
}
