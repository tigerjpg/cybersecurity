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
    IMAGE
  };

  TestimonialTableModel(QObject *parent, QSqlDatabase *db);
};

#endif // TESTIMONIALTABLEMODEL_H
