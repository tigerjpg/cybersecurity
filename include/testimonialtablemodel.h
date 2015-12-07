#ifndef TESTIMONIALTABLEMODEL_H
#define TESTIMONIALTABLEMODEL_H
#include <QSqlTableModel>
#include <QObject>

class TestimonialTableModel : public QSqlTableModel
{
  Q_OBJECT
public:
  enum Fields
  {
    ID,
    NAME,
    TESTIMONIAL,
    IMAGE,
    APPROVED
  };

  TestimonialTableModel(QObject *parent, QSqlDatabase *db);

  void Initialize();
};

#endif // TESTIMONIALTABLEMODEL_H
