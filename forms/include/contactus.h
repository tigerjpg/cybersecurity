#ifndef CONTACTUS_H
#define CONTACTUS_H

#include <QWidget>

namespace Ui {
class ContactUs;
}

class ContactUs : public QWidget
{
    Q_OBJECT

public:
    explicit ContactUs(QWidget *parent = 0);
    ~ContactUs();

private:
    Ui::ContactUs *ui;
};

#endif // CONTACTUS_H
