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
/*!
 * \brief imagebutton::SetButtonImage
 * Set the button images using three distinct QPixmaps
 */
bool imagebutton::SetButtonImage(QPixmap button, QPixmap hover, QPixmap click)
{
  SetButtonImage(button);
  SetHoverImage(hover);
  SetClickImage(click);
  return !buttonimg.isNull() && !hoverimg.isNull() && !clickimg.isNull();
}

/*!
 * \brief imagebutton::SetButtonImage
 * Set the button images using three QStrings that represent paths to the images
 */
bool imagebutton::SetButtonImage(QString button, QString hover, QString click)
{
  SetButtonImage(button);
  SetHoverImage(hover);
  SetClickImage(click);
  return !buttonimg.isNull() && !hoverimg.isNull() && !clickimg.isNull();
}

/*!
 * \brief imagebutton::SetButtonImage
 * Set the default standard button image
 */
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

/*!
 * \brief imagebutton::SetButtonImage
 * Set the default standard button image using a Qstring of the path
 */
bool imagebutton::SetButtonImage(QString imgPath)
{
  QPixmap temp(imgPath);
  SetButtonImage(temp);

  // if file is not found or openable returns false
  return !buttonimg.isNull();
}

/*!
 * \brief imagebutton::SetHoverImage
 * Set the hover button image
 */
bool imagebutton::SetHoverImage(QPixmap hover)
{
  hoverimg = hover;
  // if file is not found or openable returns false
  return !hoverimg.isNull();
}

/*!
 * \brief imagebutton::SetHoverImage
 * Set the hover button image
 */
bool imagebutton::SetHoverImage(QString imgPath)
{
  QPixmap temp(imgPath);
  SetHoverImage(temp);

  // if file is not found or openable returns false
  return !hoverimg.isNull();
}

/*!
 * \brief imagebutton::SetClickImage
 * Set the clicked button image
 */
bool imagebutton::SetClickImage(QPixmap click)
{
  clickimg = click;
  // if file is not found or openable returns false
  return !clickimg.isNull();
}

/*!
 * \brief imagebutton::SetClickImage
 * Set the clicked button image
 */
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
/*!
 * \brief imagebutton::resizeEvent
 * redefines the resize event from QObject to update the image size
 */
void imagebutton::resizeEvent(QResizeEvent *e)
{
  resizePicture(this->width(), this->height());
  QWidget::resizeEvent(e);
}

/************************/
/* MOUSE EVENT HANDLERS */
/************************/
/*!
 * \brief imagebutton::enterEvent
 * redefines the mouse enter event from QObject to update the image displayed
 */
void imagebutton::enterEvent(QEvent *e)
{
  ChangePicture(hoverimg);

  // do any normal pushbutton stuff from parent class
  QPushButton::enterEvent(e);
}

/*!
 * \brief imagebutton::leaveEvent
 * redefines the mouse leave event from QObject to update the image displayed
 */
void imagebutton::leaveEvent(QEvent *e)
{
  if(!this->hasFocus())
    ChangePicture(buttonimg);

  // do any normal pushbutton stuff from parent class
  QPushButton::leaveEvent(e);
}

/*!
 * \brief imagebutton::mousePressEvent
 * redefines the mouse press event from QObject to update the image displayed
 */
void imagebutton::mousePressEvent(QMouseEvent *e)
{
  ChangePicture(clickimg);
  emit pressed();
}

/*!
 * \brief imagebutton::mouseReleaseEvent
 * redefines the mouse release event from QObject to update the image displayed
 */
void imagebutton::mouseReleaseEvent(QMouseEvent *e)
{
  ChangePicture(hoverimg);
  emit released();
  emit clicked();
}

/***************************/
/* KEYBOARD EVENT HANDLERS */
/***************************/
/*!
 * \brief imagebutton::focusInEvent
 * redefines the keyboard focus event from QObject to update the image displayed
 */
void imagebutton::focusInEvent(QFocusEvent *e)
{
  ChangePicture(hoverimg);
  QPushButton::focusInEvent(e);
}

/*!
 * \brief imagebutton::focusOutEvent
 * redefines the keyboard focus lost event from QObject to update the image displayed
 */
void imagebutton::focusOutEvent(QFocusEvent *e)
{
  if(!this->underMouse())
    ChangePicture(buttonimg);

  QPushButton::focusOutEvent(e);
}

/*!
 * \brief imagebutton::keyPressEvent
 * redefines the keyboard key pressed event from QObject to update the image displayed
 */
void imagebutton::keyPressEvent(QKeyEvent *e)
{
  ChangePicture(clickimg);
  emit pressed();
  emit clicked();
}

/*!
 * \brief imagebutton::keyReleaseEvent
 * redefines the keyboard release event from QObject to update the image displayed
 */
void imagebutton::keyReleaseEvent(QKeyEvent *e)
{
  ChangePicture(hoverimg);
  emit released();
}

/******************/
/* HELPER METHODS */
/******************/
/*!
 * \brief imagebutton::resizePicture
 * Resizes the picture currently displayed to fit the given size
 * \param [in] w the width to resize to
 * \param [in] h the height to resize to
 */
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

/*!
 * \brief imagebutton::ChangePicture
 * Helper Method that changes the picture displayed on the button
 * \param [in] picture the picture to display on the button
 */
void imagebutton::ChangePicture(QPixmap picture)
{
  // This makes the button as an image by using the pallate brush
  QPalette pic;
  pic.setBrush(backgroundRole(), QBrush(picture.scaled(this->width(), this->height(), Qt::KeepAspectRatio) ) );
  this->setPalette(pic);

  // Creates the click mask from the image
  this->setMask( (picture.scaled(this->width(),this->height(), Qt::KeepAspectRatio)).mask() );
}
