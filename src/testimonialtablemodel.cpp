#include "testimonialtablemodel.h"

TestimonialTableModel::TestimonialTableModel(QObject *parent, QSqlDatabase *db)
                      :QSqlTableModel(parent, *db)
{
  this->setTable("testimonials");
  this->select();
}

void TestimonialTableModel::Initialize()
{
  this->setTable("testimonials");
  this->setFilter("");
  this->select();
}
