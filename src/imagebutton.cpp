#include "imagebutton.h"

/********************************/
/* CONSTRUCTORS AND DESTRUCTORS */
/********************************/
imagebutton::imagebutton(QWidget *parent)
  : QPushButton(parent)
{
  this->setFlat(true);
  this->setAutoFillBackground(true);
  this->setText("");

  // prevents the button from getting focus from mouse action, but tabbing still works
  this->setFocusPolicy(Qt::NoFocus);

  //this->setStyleSheet("QPushButton{border: 0;outline: 0px;}");
  qDebug() << "constructor called";
}

/*****************/
/* SET FUNCTIONS */
/*****************/
bool imagebutton::SetButtonImage(QPixmap button, QPixmap hover, QPixmap click)
{
  SetButtonImage(button);
  SetHoverImage(hover);
  SetClickImage(click);
  return !buttonimg.isNull() && !hoverimg.isNull() && !clickimg.isNull();
}

bool imagebutton::SetButtonImage(QString button, QString hover, QString click)
{
  SetButtonImage(button);
  SetHoverImage(hover);
  SetClickImage(click);
  return !buttonimg.isNull() && !hoverimg.isNull() && !clickimg.isNull();
}

bool imagebutton::SetButtonImage(QPixmap button)
{
  // Sets the standard button image and clear out any text
  buttonimg = button;
  this->setText("");
  if(!buttonimg.isNull())
    ChangePicture(buttonimg);

  // if file is not found or openable returns false
  return !buttonimg.isNull();
}

bool imagebutton::SetButtonImage(QString imgPath)
{
  QPixmap temp(imgPath);
  SetButtonImage(temp);

  // if file is not found or openable returns false
  return !buttonimg.isNull();
}

bool imagebutton::SetHoverImage(QPixmap hover)
{
  hoverimg = hover;
  // if file is not found or openable returns false
  return !hoverimg.isNull();
}

bool imagebutton::SetHoverImage(QString imgPath)
{
  QPixmap temp(imgPath);
  SetHoverImage(temp);

  // if file is not found or openable returns false
  return !hoverimg.isNull();
}

bool imagebutton::SetClickImage(QPixmap click)
{
  clickimg = click;
  // if file is not found or openable returns false
  return !clickimg.isNull();
}

bool imagebutton::SetClickImage(QString imgPath)
{
  QPixmap temp(imgPath);
  SetClickImage(temp);
  // if file is not found or openable returns false
  return !clickimg.isNull();
}


/*******************/
/* EVENT REDEFINES */
/*******************/
void imagebutton::resizeEvent(QResizeEvent *e)
{
  resizePicture(this->width(), this->height());
  QWidget::resizeEvent(e);
}

/************************/
/* MOUSE EVENT HANDLERS */
/************************/
void imagebutton::enterEvent(QEvent *e)
{
  ChangePicture(hoverimg);

  // do any normal pushbutton stuff from parent class
  QPushButton::enterEvent(e);
}

void imagebutton::leaveEvent(QEvent *e)
{
  if(!this->hasFocus())
    ChangePicture(buttonimg);

  // do any normal pushbutton stuff from parent class
  QPushButton::leaveEvent(e);
}

void imagebutton::mousePressEvent(QMouseEvent *e)
{
  ChangePicture(clickimg);
  emit pressed();
}

void imagebutton::mouseReleaseEvent(QMouseEvent *e)
{
  ChangePicture(hoverimg);
  emit released();
  emit clicked();
}

/***************************/
/* KEYBOARD EVENT HANDLERS */
/***************************/
void imagebutton::focusInEvent(QFocusEvent *e)
{
  ChangePicture(hoverimg);
  QPushButton::focusInEvent(e);
}

void imagebutton::focusOutEvent(QFocusEvent *e)
{
  if(!this->underMouse())
    ChangePicture(buttonimg);

  QPushButton::focusOutEvent(e);
}

void imagebutton::keyPressEvent(QKeyEvent *e)
{
  ChangePicture(clickimg);
  emit pressed();
  emit clicked();
}

void imagebutton::keyReleaseEvent(QKeyEvent *e)
{
  ChangePicture(hoverimg);
  emit released();
}

/******************/
/* HELPER METHODS */
/******************/
void imagebutton::resizePicture(int w, int h)
{
  qDebug() << "resizing to width: " << w << " height: " << h;
  QPixmap  tempImg = buttonimg.scaled(w, h, Qt::KeepAspectRatio);

  QPalette pic;
  pic.setBrush(backgroundRole(), QBrush(tempImg) );
  this->setPalette(pic);

  // Creates the click mask from the image
  this->setMask(tempImg.mask());
}

void imagebutton::ChangePicture(QPixmap picture)
{
  // This makes the button as an image by using the pallate brush
  QPalette pic;
  pic.setBrush(backgroundRole(), QBrush(picture.scaled(this->width(), this->height(), Qt::KeepAspectRatio) ) );
  this->setPalette(pic);

  // Creates the click mask from the image
  this->setMask( (picture.scaled(this->width(),this->height(), Qt::KeepAspectRatio)).mask() );
}
