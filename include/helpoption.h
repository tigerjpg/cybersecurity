#ifndef HELPOPTION_H
#define HELPOPTION_H

#include <QWidget>

namespace Ui {
class HelpOption;
}

class HelpOption : public QWidget
{
    Q_OBJECT

public:
    explicit HelpOption(QWidget *parent = 0);
    ~HelpOption();

private slots:
    void on_OKExitHelpB_clicked();

    void on_LogInInstructions_clicked();

    void on_RequestPamInstructions_clicked();

    void on_ReadTestimonialsInstructions_clicked();

    void on_PurchaseInstructions_clicked();

    void on_LogOffInstructions_clicked();

    void on_AboutUsInstructions_clicked();

private:
    Ui::HelpOption *ui;
};

#endif // HELPOPTION_H
