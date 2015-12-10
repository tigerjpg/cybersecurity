#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QVector>
#include <QPixmap>
//#include <QPropertyAnimation>
#include <QMovie>
#include <QLabel>
#include <QSound>
#include <QList>
#include "database.h"
#include "customertablemodel.h"
#include "testimonialtablemodel.h"
#include "addtestimonialpopup.h"
#include "viewpurchasespopup.h"
#include "addcustomerpopup.h"
#include "helpoption.h"
#include "errorpopup.h"
#include "contactus.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT


public:
  enum Page {
    INTRO,
    LOGIN,
    REGISTER,
    INFORMATION,
    ADMINISTRATOR,
    CUSTOMER
  };

  enum CustomerPage {
    CUST_PRODUCTS,
    CUST_MAINTENANCE,
    CUST_TESTIMONIALS,
    CUST_PURCHASE
  };

  struct ProductInfo {
    QString productName;
    QString html;
    double  price;
  };

  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
public slots:

private slots:

  void on_login_buttonBox_accepted();

  void on_login_buttonBox_rejected();

  void on_customer_tableView_activated(const QModelIndex &index);

  void on_password_line_returnPressed();

  void on_customer_key_customers_checkBox_toggled(bool checked);

  void on_administrator_toolBox_currentChanged(int index);

  void on_testimonial_add_button_clicked();

  void on_testimonial_remove_button_clicked();

  void on_testimonial_approve_button_clicked();

  void on_customer_remove_button_clicked();

  void on_customer_interest_comboBox_currentIndexChanged(int index);

  void on_customer_purchase_button_clicked();

  void on_customer_submit_changes_button_clicked();

private slots:
  void Welcome();
  void Click();
  void on_finished_intro();
  void on_welcomeBtn_clicked();

  void on_RegisterButton_clicked();
  // SLOTS-Registrations fields-----------------------
  void on_username_line_2_editingFinished();
  void on_password_line_2_editingFinished();
  void on_company_line_editingFinished();
  void on_address_line_editingFinished();
  void on_interest_box_currentIndexChanged(int index);
  void on_terms_box_toggled(bool checked);
  //--------------------------------------------------
  void on_register_okay_button_clicked();
  void on_register_cancel_button_clicked();

  void on_InformationButton_clicked();
  // SLOTS-Information buttons------------------------
  void on_GeneralInfoButton_clicked();
  void on_ConceptOfOperations_clicked();
  void on_SupportedPlattaforms_clicked();
  //--------------------------------------------------
  void on_OKgoBackLogIn_clicked();

  void on_customer_add_pushButton_clicked();

  void on_customer_send_pamphlet_button_clicked();


  void on_admin_logout_button_clicked();

  void on_toolBox_currentChanged(int index);

  void on_customer_testimonial_slider_sliderMoved(int position);

  void on_customer_testimonial_slider_valueChanged(int value);

  void on_customer_products_slider_valueChanged(int value);

  void on_customer_purchase_purchaseButton_clicked();

  void on_pushButton_2_clicked();

  void on_customer_logout_button_clicked();

  void on_add_testimonial_buttonBox_accepted();

  void on_add_testimonial_text_textChanged();

  void on_add_testimonial_buttonBox_rejected();

  void on_contact_button_clicked();

  void on_customer_submit_changes_help_button_clicked();

  void on_testimonial_add_help_button_clicked();

  void on_help_button_clicked();

private:
  // Function to check if all fields in the registration table are filled
  bool RegistrationCompleted();
  // function to create db entries for user
  bool Register();
  // function to initialize the maintenance plane page
  void InitializeMaintenance();


  void changeBackground(int index);
  void setBackground(QPixmap picture);
  void setBackground(QMovie *movie, int speed);
  void WelcomeAnimation();
  void Register_ClearForms();
  void SetTestimonialView(int index);
  void UpdateTestimonialList();
  void LoadProductList();
  void SetActiveUser(QString id);
  void ClearAllPurchaseCheckboxes();
  void InitCustomerPurchaseTableView();

  Ui::MainWindow *ui;
  Database *db;
  CustomerTableModel *cTableModel;
  TestimonialTableModel *tTableModel;
  PurchasesTableModel *pTableModel;
  QVector<QPixmap> mainBackground;
  QList<QSqlRecord> *testimonials;
  QList<ProductInfo> ProductInfoList;
  QLabel *background;
  QString activeUserId;
  void InitTestimonialTableView();
  void InitCustomerTableView();
};

#endif // MAINWINDOW_H
