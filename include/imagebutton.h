/**
 * \class imagebutton
 *
 * \brief Provides buttons based on images for a friendly user experience
 *
 * There are many ways to do this but this provides a easy and uniform way to make buttons
 * out of images with an alpha layer (transparency) such as png files. The buttons will
 * only be clickable where the image is.
 *
 * \note shortcut key not implemented, but can do if needed
 *
 * \author Ethan Slattery
 *
 * \version $Revision: 1.0 $
 *
 * \date $Date: 2015/11/7 19:00:00 $
 */

#ifndef IMGBUTTON
#define IMGBUTTON

#include <QPushButton>
#include <QEvent>
#include <QPixmap>
#include <QBitmap>
#include <QDebug>

class imagebutton : public QPushButton
{
    public:
    /* Constructor and Destructors */
        /// creates the button, and will act as a normal pushbutton till configured
        imagebutton(QWidget *parent = 0);

        /// creates a pre-configured pushbutton
        imagebutton(QPixmap button, QPixmap hover, QPixmap click, QWidget *parent = 0);

    /* SET FUNCTIONS */
        /// Sets the Standard Button Image using a QImage
        bool SetButtonImage(QPixmap button);
        /// Sets the Standard Button Image using a path to the picture
        bool SetButtonImage(QString imgPath);

        /// Sets the Hover Button Image using a QImage
        bool SetHoverImage(QPixmap hover);
        /// Sets the Hover Button Image using a path to the picture
        bool SetHoverImage(QString imgPath);

        /// Sets the Clicked Button Image using a QImage
        bool SetClickImage(QPixmap click);
        /// Sets the Clicked Button Image using a path to the picture
        bool SetClickImage(QString imgPath);

    public slots:
    /* MOUSE EVENT HANDLERS */
        /// Changes the image on the button when the mouse enters the region
        void enterEvent(QEvent *e);
        /// Changes the image on the button when the mouse leaves the region
        void leaveEvent(QEvent *e);
        /// Changes the picture upon mouse click
        void mousePressEvent(QMouseEvent *e);
        /// Changes the picture upon mouse release
        void mouseReleaseEvent(QMouseEvent *e);

    /* KEYBOARD EVENT HANDLERS */
        /// changes the picture for keyboard focus gained
        void focusInEvent(QFocusEvent *e);
        /// changes the picture when keyboard focus lost
        void focusOutEvent(QFocusEvent *e);
        /// changes the picture for keyboard activation
        void keyPressEvent(QKeyEvent *e);
        /// changes the picture for key release event
        void keyReleaseEvent(QKeyEvent *e);


    private:
    /* Private Methods */
        void ChangePicture(QPixmap);

    /* Private Data Members */
        QPixmap buttonimg; ///< Normal button image
        QPixmap hoverimg;  ///< Image for Hovering
        QPixmap clickimg;  ///< Image for click event
};

#endif // IMGBUTTON

