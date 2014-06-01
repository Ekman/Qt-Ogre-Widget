#ifndef QOGREWIDGET_H
#define QOGREWIDGET_H

#include "PreProcessor.h"
#include "WindowEventListener.h"
#include "QOgreWindow.h"

namespace QtOgre {

/**
 * @brief Qt widget class that can host an Ogre Rendering window
 */
class QOgreWidget : public QWidget {
	Q_OBJECT
public:
	/**
	 * @brief QOgreWidget
	 * @param parent Parent widget/window
	 * @param windowEvent Callback for window events
	 * @param setupEvent Callback for setup events
	 */
	QOgreWidget(QWidget *parent, WindowEventListener* windowEvent);
	virtual ~QOgreWidget();

	/**
	 * @brief createRenderWindow Create the rendering window and attach it to this widget
	 */
	void createRenderWindow();

	/**
	 * @brief calculateMouseCenter Calculate the mouse center position. Stored internally!
	 */
	void calculateMouseCenter();

	/**
	 * @brief getWindowHandle Get the window handle for this widget, denpending on OS
	 * @return Window handle to this widget
	 */
	Ogre::String getWindowHandle() const;

	/**
	 * @brief getRenderOptions Return render options that are needed to create the Ogre rendering window
	 * @return Associative list of options
	 */
	Ogre::NameValuePairList getRenderOptions() const;

	// Qt funcction
	virtual void paintEvent(QPaintEvent* pEvent);
	virtual void resizeEvent(QResizeEvent* rEvent);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual QPaintEngine* paintEngine() const;
private:
	/**
	 * @brief renderWindow Contains a refernce to the rendering window from the createRenderWindow call
	 */
	Ogre::RenderWindow *renderWindow;
	/**
	 * @brief mouseCenter Contains the mouse center coordinates
	 */
	QPoint mouseCenter;
	/**
	 * @brief windowEvent Listener for action events
	 */
	WindowEventListener* windowEvent;

	// Disable copying of this object, Qt::Widget doesnt allow it!
	inline QOgreWidget(const QOgreWidget &widget) {
		throw std::runtime_error("Not allowed to copy QOgreWidget");
	}
};

}

#endif // QOGREWIDGET_H
